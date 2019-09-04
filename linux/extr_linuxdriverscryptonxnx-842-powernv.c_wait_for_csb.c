#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nx842_workmem {int /*<<< orphan*/  start; } ;
struct coprocessor_status_block {int flags; int cc; int ce; int /*<<< orphan*/  count; scalar_t__ cs; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
#define  CSB_CC_ABORT 175 
#define  CSB_CC_CHAIN 174 
#define  CSB_CC_CRC_MISMATCH 173 
#define  CSB_CC_DATA_LENGTH 172 
#define  CSB_CC_DDE_OVERFLOW 171 
#define  CSB_CC_EXCEED_BYTE_COUNT 170 
#define  CSB_CC_EXCESSIVE_DDE 169 
#define  CSB_CC_HW 168 
#define  CSB_CC_HW_EXPIRED_TIMER 167 
#define  CSB_CC_INTERNAL 166 
#define  CSB_CC_INVALID_ALIGN 165 
#define  CSB_CC_INVALID_CRB 164 
#define  CSB_CC_INVALID_DDE 163 
#define  CSB_CC_INVALID_OPERAND 162 
#define  CSB_CC_NOSPC 161 
#define  CSB_CC_OPERAND_OVERLAP 160 
#define  CSB_CC_PRIVILEGE 159 
#define  CSB_CC_PROTECTION 158 
#define  CSB_CC_PROTECTION_DUP1 157 
#define  CSB_CC_PROTECTION_DUP2 156 
#define  CSB_CC_PROTECTION_DUP3 155 
#define  CSB_CC_PROTECTION_DUP4 154 
#define  CSB_CC_PROTECTION_DUP5 153 
#define  CSB_CC_PROTECTION_DUP6 152 
#define  CSB_CC_PROVISION 151 
#define  CSB_CC_RD_EXTERNAL 150 
#define  CSB_CC_RD_EXTERNAL_DUP1 149 
#define  CSB_CC_RD_EXTERNAL_DUP2 148 
#define  CSB_CC_RD_EXTERNAL_DUP3 147 
#define  CSB_CC_SEGMENTED_DDL 146 
#define  CSB_CC_SEQUENCE 145 
#define  CSB_CC_SESSION 144 
#define  CSB_CC_SUCCESS 143 
#define  CSB_CC_TEMPL_INVALID 142 
#define  CSB_CC_TEMPL_OVERFLOW 141 
#define  CSB_CC_TPBC_GT_SPBC 140 
#define  CSB_CC_TRANSLATION 139 
#define  CSB_CC_TRANSLATION_DUP1 138 
#define  CSB_CC_TRANSLATION_DUP2 137 
#define  CSB_CC_TRANSLATION_DUP3 136 
#define  CSB_CC_TRANSLATION_DUP4 135 
#define  CSB_CC_TRANSLATION_DUP5 134 
#define  CSB_CC_TRANSLATION_DUP6 133 
#define  CSB_CC_TRANSPORT 132 
#define  CSB_CC_UNKNOWN_CODE 131 
#define  CSB_CC_WR_EXTERNAL 130 
#define  CSB_CC_WR_PROTECTION 129 
#define  CSB_CC_WR_TRANSLATION 128 
 int CSB_CE_INCOMPLETE ; 
 int CSB_CE_TERMINATION ; 
 int CSB_CE_TPBC ; 
 int CSB_CH ; 
 int /*<<< orphan*/  CSB_ERR (struct coprocessor_status_block*,char*,...) ; 
 int /*<<< orphan*/  CSB_ERR_ADDR (struct coprocessor_status_block*,char*) ; 
 int CSB_F ; 
 int CSB_V ; 
 int /*<<< orphan*/  CSB_WAIT_MAX ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOSPC ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int wait_for_csb(struct nx842_workmem *wmem,
			struct coprocessor_status_block *csb)
{
	ktime_t start = wmem->start, now = ktime_get();
	ktime_t timeout = ktime_add_ms(start, CSB_WAIT_MAX);

	while (!(READ_ONCE(csb->flags) & CSB_V)) {
		cpu_relax();
		now = ktime_get();
		if (ktime_after(now, timeout))
			break;
	}

	/* hw has updated csb and output buffer */
	barrier();

	/* check CSB flags */
	if (!(csb->flags & CSB_V)) {
		CSB_ERR(csb, "CSB still not valid after %ld us, giving up",
			(long)ktime_us_delta(now, start));
		return -ETIMEDOUT;
	}
	if (csb->flags & CSB_F) {
		CSB_ERR(csb, "Invalid CSB format");
		return -EPROTO;
	}
	if (csb->flags & CSB_CH) {
		CSB_ERR(csb, "Invalid CSB chaining state");
		return -EPROTO;
	}

	/* verify CSB completion sequence is 0 */
	if (csb->cs) {
		CSB_ERR(csb, "Invalid CSB completion sequence");
		return -EPROTO;
	}

	/* check CSB Completion Code */
	switch (csb->cc) {
	/* no error */
	case CSB_CC_SUCCESS:
		break;
	case CSB_CC_TPBC_GT_SPBC:
		/* not an error, but the compressed data is
		 * larger than the uncompressed data :(
		 */
		break;

	/* input data errors */
	case CSB_CC_OPERAND_OVERLAP:
		/* input and output buffers overlap */
		CSB_ERR(csb, "Operand Overlap error");
		return -EINVAL;
	case CSB_CC_INVALID_OPERAND:
		CSB_ERR(csb, "Invalid operand");
		return -EINVAL;
	case CSB_CC_NOSPC:
		/* output buffer too small */
		return -ENOSPC;
	case CSB_CC_ABORT:
		CSB_ERR(csb, "Function aborted");
		return -EINTR;
	case CSB_CC_CRC_MISMATCH:
		CSB_ERR(csb, "CRC mismatch");
		return -EINVAL;
	case CSB_CC_TEMPL_INVALID:
		CSB_ERR(csb, "Compressed data template invalid");
		return -EINVAL;
	case CSB_CC_TEMPL_OVERFLOW:
		CSB_ERR(csb, "Compressed data template shows data past end");
		return -EINVAL;
	case CSB_CC_EXCEED_BYTE_COUNT:	/* P9 or later */
		/*
		 * DDE byte count exceeds the limit specified in Maximum
		 * byte count register.
		 */
		CSB_ERR(csb, "DDE byte count exceeds the limit");
		return -EINVAL;

	/* these should not happen */
	case CSB_CC_INVALID_ALIGN:
		/* setup_ddl should have detected this */
		CSB_ERR_ADDR(csb, "Invalid alignment");
		return -EINVAL;
	case CSB_CC_DATA_LENGTH:
		/* setup_ddl should have detected this */
		CSB_ERR(csb, "Invalid data length");
		return -EINVAL;
	case CSB_CC_WR_TRANSLATION:
	case CSB_CC_TRANSLATION:
	case CSB_CC_TRANSLATION_DUP1:
	case CSB_CC_TRANSLATION_DUP2:
	case CSB_CC_TRANSLATION_DUP3:
	case CSB_CC_TRANSLATION_DUP4:
	case CSB_CC_TRANSLATION_DUP5:
	case CSB_CC_TRANSLATION_DUP6:
		/* should not happen, we use physical addrs */
		CSB_ERR_ADDR(csb, "Translation error");
		return -EPROTO;
	case CSB_CC_WR_PROTECTION:
	case CSB_CC_PROTECTION:
	case CSB_CC_PROTECTION_DUP1:
	case CSB_CC_PROTECTION_DUP2:
	case CSB_CC_PROTECTION_DUP3:
	case CSB_CC_PROTECTION_DUP4:
	case CSB_CC_PROTECTION_DUP5:
	case CSB_CC_PROTECTION_DUP6:
		/* should not happen, we use physical addrs */
		CSB_ERR_ADDR(csb, "Protection error");
		return -EPROTO;
	case CSB_CC_PRIVILEGE:
		/* shouldn't happen, we're in HYP mode */
		CSB_ERR(csb, "Insufficient Privilege error");
		return -EPROTO;
	case CSB_CC_EXCESSIVE_DDE:
		/* shouldn't happen, setup_ddl doesn't use many dde's */
		CSB_ERR(csb, "Too many DDEs in DDL");
		return -EINVAL;
	case CSB_CC_TRANSPORT:
	case CSB_CC_INVALID_CRB:	/* P9 or later */
		/* shouldn't happen, we setup CRB correctly */
		CSB_ERR(csb, "Invalid CRB");
		return -EINVAL;
	case CSB_CC_INVALID_DDE:	/* P9 or later */
		/*
		 * shouldn't happen, setup_direct/indirect_dde creates
		 * DDE right
		 */
		CSB_ERR(csb, "Invalid DDE");
		return -EINVAL;
	case CSB_CC_SEGMENTED_DDL:
		/* shouldn't happen, setup_ddl creates DDL right */
		CSB_ERR(csb, "Segmented DDL error");
		return -EINVAL;
	case CSB_CC_DDE_OVERFLOW:
		/* shouldn't happen, setup_ddl creates DDL right */
		CSB_ERR(csb, "DDE overflow error");
		return -EINVAL;
	case CSB_CC_SESSION:
		/* should not happen with ICSWX */
		CSB_ERR(csb, "Session violation error");
		return -EPROTO;
	case CSB_CC_CHAIN:
		/* should not happen, we don't use chained CRBs */
		CSB_ERR(csb, "Chained CRB error");
		return -EPROTO;
	case CSB_CC_SEQUENCE:
		/* should not happen, we don't use chained CRBs */
		CSB_ERR(csb, "CRB sequence number error");
		return -EPROTO;
	case CSB_CC_UNKNOWN_CODE:
		CSB_ERR(csb, "Unknown subfunction code");
		return -EPROTO;

	/* hardware errors */
	case CSB_CC_RD_EXTERNAL:
	case CSB_CC_RD_EXTERNAL_DUP1:
	case CSB_CC_RD_EXTERNAL_DUP2:
	case CSB_CC_RD_EXTERNAL_DUP3:
		CSB_ERR_ADDR(csb, "Read error outside coprocessor");
		return -EPROTO;
	case CSB_CC_WR_EXTERNAL:
		CSB_ERR_ADDR(csb, "Write error outside coprocessor");
		return -EPROTO;
	case CSB_CC_INTERNAL:
		CSB_ERR(csb, "Internal error in coprocessor");
		return -EPROTO;
	case CSB_CC_PROVISION:
		CSB_ERR(csb, "Storage provision error");
		return -EPROTO;
	case CSB_CC_HW:
		CSB_ERR(csb, "Correctable hardware error");
		return -EPROTO;
	case CSB_CC_HW_EXPIRED_TIMER:	/* P9 or later */
		CSB_ERR(csb, "Job did not finish within allowed time");
		return -EPROTO;

	default:
		CSB_ERR(csb, "Invalid CC %d", csb->cc);
		return -EPROTO;
	}

	/* check Completion Extension state */
	if (csb->ce & CSB_CE_TERMINATION) {
		CSB_ERR(csb, "CSB request was terminated");
		return -EPROTO;
	}
	if (csb->ce & CSB_CE_INCOMPLETE) {
		CSB_ERR(csb, "CSB request not complete");
		return -EPROTO;
	}
	if (!(csb->ce & CSB_CE_TPBC)) {
		CSB_ERR(csb, "TPBC not provided, unknown target length");
		return -EPROTO;
	}

	/* successful completion */
	pr_debug_ratelimited("Processed %u bytes in %lu us\n",
			     be32_to_cpu(csb->count),
			     (unsigned long)ktime_us_delta(now, start));

	return 0;
}