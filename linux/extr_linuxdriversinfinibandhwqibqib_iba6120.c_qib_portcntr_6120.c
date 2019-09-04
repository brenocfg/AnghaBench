#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {int first_user_ctxt; TYPE_1__* cspec; int /*<<< orphan*/  pcidev; } ;
struct TYPE_2__ {unsigned long long lli_errs; unsigned long long overrun_thresh_errs; unsigned long long pma_sample_status; unsigned long long ibsymsnap; unsigned long long ibsymdelta; unsigned long long iblnkerrsnap; unsigned long long iblnkerrdelta; unsigned long long rxfc_unsupvl_errs; scalar_t__ ibdeltainprog; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  QIBPORTCNTR_BADFORMAT 181 
#define  QIBPORTCNTR_ERRICRC 180 
#define  QIBPORTCNTR_ERRLINK 179 
#define  QIBPORTCNTR_ERRLPCRC 178 
#define  QIBPORTCNTR_ERRPKEY 177 
#define  QIBPORTCNTR_ERRVCRC 176 
#define  QIBPORTCNTR_ERR_RLEN 175 
#define  QIBPORTCNTR_EXCESSBUFOVFL 174 
#define  QIBPORTCNTR_IBLINKDOWN 173 
#define  QIBPORTCNTR_IBLINKERRRECOV 172 
#define  QIBPORTCNTR_IBSYMBOLERR 171 
#define  QIBPORTCNTR_INVALIDRLEN 170 
#define  QIBPORTCNTR_KHDROVFL 169 
#define  QIBPORTCNTR_LLI 168 
#define  QIBPORTCNTR_PKTRCV 167 
#define  QIBPORTCNTR_PKTSEND 166 
#define  QIBPORTCNTR_PSINTERVAL 165 
#define  QIBPORTCNTR_PSRCVDATA 164 
#define  QIBPORTCNTR_PSRCVPKTS 163 
#define  QIBPORTCNTR_PSSTART 162 
#define  QIBPORTCNTR_PSSTAT 161 
#define  QIBPORTCNTR_PSXMITDATA 160 
#define  QIBPORTCNTR_PSXMITPKTS 159 
#define  QIBPORTCNTR_PSXMITWAIT 158 
#define  QIBPORTCNTR_RCVEBP 157 
#define  QIBPORTCNTR_RCVOVFL 156 
#define  QIBPORTCNTR_RXDROPPKT 155 
#define  QIBPORTCNTR_RXLOCALPHYERR 154 
#define  QIBPORTCNTR_RXVLERR 153 
#define  QIBPORTCNTR_SENDSTALL 152 
#define  QIBPORTCNTR_UNSUPVL 151 
#define  QIBPORTCNTR_VL15PKTDROP 150 
#define  QIBPORTCNTR_WORDRCV 149 
#define  QIBPORTCNTR_WORDSEND 148 
#define  cr_badformat 147 
#define  cr_err_rlen 146 
#define  cr_erricrc 145 
#define  cr_errlink 144 
#define  cr_errlpcrc 143 
#define  cr_errpkey 142 
#define  cr_errvcrc 141 
#define  cr_iblinkdown 140 
#define  cr_iblinkerrrecov 139 
#define  cr_ibsymbolerr 138 
#define  cr_invalidrlen 137 
#define  cr_pktrcv 136 
#define  cr_pktsend 135 
 int cr_portovfl ; 
#define  cr_rcvebp 134 
#define  cr_rcvovfl 133 
#define  cr_rxdroppkt 132 
#define  cr_sendstall 131 
#define  cr_txunsupvl 130 
#define  cr_wordrcv 129 
#define  cr_wordsend 128 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,size_t) ; 
 unsigned long long read_6120_creg (struct qib_devdata*,int) ; 
 unsigned long long read_6120_creg32 (struct qib_devdata*,int) ; 

__attribute__((used)) static u64 qib_portcntr_6120(struct qib_pportdata *ppd, u32 reg)
{
	u64 ret = 0ULL;
	struct qib_devdata *dd = ppd->dd;
	u16 creg;
	/* 0xffff for unimplemented or synthesized counters */
	static const u16 xlator[] = {
		[QIBPORTCNTR_PKTSEND] = cr_pktsend,
		[QIBPORTCNTR_WORDSEND] = cr_wordsend,
		[QIBPORTCNTR_PSXMITDATA] = 0xffff,
		[QIBPORTCNTR_PSXMITPKTS] = 0xffff,
		[QIBPORTCNTR_PSXMITWAIT] = 0xffff,
		[QIBPORTCNTR_SENDSTALL] = cr_sendstall,
		[QIBPORTCNTR_PKTRCV] = cr_pktrcv,
		[QIBPORTCNTR_PSRCVDATA] = 0xffff,
		[QIBPORTCNTR_PSRCVPKTS] = 0xffff,
		[QIBPORTCNTR_RCVEBP] = cr_rcvebp,
		[QIBPORTCNTR_RCVOVFL] = cr_rcvovfl,
		[QIBPORTCNTR_WORDRCV] = cr_wordrcv,
		[QIBPORTCNTR_RXDROPPKT] = cr_rxdroppkt,
		[QIBPORTCNTR_RXLOCALPHYERR] = 0xffff,
		[QIBPORTCNTR_RXVLERR] = 0xffff,
		[QIBPORTCNTR_ERRICRC] = cr_erricrc,
		[QIBPORTCNTR_ERRVCRC] = cr_errvcrc,
		[QIBPORTCNTR_ERRLPCRC] = cr_errlpcrc,
		[QIBPORTCNTR_BADFORMAT] = cr_badformat,
		[QIBPORTCNTR_ERR_RLEN] = cr_err_rlen,
		[QIBPORTCNTR_IBSYMBOLERR] = cr_ibsymbolerr,
		[QIBPORTCNTR_INVALIDRLEN] = cr_invalidrlen,
		[QIBPORTCNTR_UNSUPVL] = cr_txunsupvl,
		[QIBPORTCNTR_EXCESSBUFOVFL] = 0xffff,
		[QIBPORTCNTR_ERRLINK] = cr_errlink,
		[QIBPORTCNTR_IBLINKDOWN] = cr_iblinkdown,
		[QIBPORTCNTR_IBLINKERRRECOV] = cr_iblinkerrrecov,
		[QIBPORTCNTR_LLI] = 0xffff,
		[QIBPORTCNTR_PSINTERVAL] = 0xffff,
		[QIBPORTCNTR_PSSTART] = 0xffff,
		[QIBPORTCNTR_PSSTAT] = 0xffff,
		[QIBPORTCNTR_VL15PKTDROP] = 0xffff,
		[QIBPORTCNTR_ERRPKEY] = cr_errpkey,
		[QIBPORTCNTR_KHDROVFL] = 0xffff,
	};

	if (reg >= ARRAY_SIZE(xlator)) {
		qib_devinfo(ppd->dd->pcidev,
			 "Unimplemented portcounter %u\n", reg);
		goto done;
	}
	creg = xlator[reg];

	/* handle counters requests not implemented as chip counters */
	if (reg == QIBPORTCNTR_LLI)
		ret = dd->cspec->lli_errs;
	else if (reg == QIBPORTCNTR_EXCESSBUFOVFL)
		ret = dd->cspec->overrun_thresh_errs;
	else if (reg == QIBPORTCNTR_KHDROVFL) {
		int i;

		/* sum over all kernel contexts */
		for (i = 0; i < dd->first_user_ctxt; i++)
			ret += read_6120_creg32(dd, cr_portovfl + i);
	} else if (reg == QIBPORTCNTR_PSSTAT)
		ret = dd->cspec->pma_sample_status;
	if (creg == 0xffff)
		goto done;

	/*
	 * only fast incrementing counters are 64bit; use 32 bit reads to
	 * avoid two independent reads when on opteron
	 */
	if (creg == cr_wordsend || creg == cr_wordrcv ||
	    creg == cr_pktsend || creg == cr_pktrcv)
		ret = read_6120_creg(dd, creg);
	else
		ret = read_6120_creg32(dd, creg);
	if (creg == cr_ibsymbolerr) {
		if (dd->cspec->ibdeltainprog)
			ret -= ret - dd->cspec->ibsymsnap;
		ret -= dd->cspec->ibsymdelta;
	} else if (creg == cr_iblinkerrrecov) {
		if (dd->cspec->ibdeltainprog)
			ret -= ret - dd->cspec->iblnkerrsnap;
		ret -= dd->cspec->iblnkerrdelta;
	}
	if (reg == QIBPORTCNTR_RXDROPPKT) /* add special cased count */
		ret += dd->cspec->rxfc_unsupvl_errs;

done:
	return ret;
}