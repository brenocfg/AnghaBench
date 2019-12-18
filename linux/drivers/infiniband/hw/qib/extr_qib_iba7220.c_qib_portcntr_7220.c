#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct qib_pportdata {TYPE_1__* cpspec; struct qib_devdata* dd; } ;
struct qib_devdata {int first_user_ctxt; TYPE_3__* pport; int /*<<< orphan*/  pcidev; } ;
struct TYPE_6__ {TYPE_2__* cpspec; } ;
struct TYPE_5__ {unsigned long long ibsymdelta; unsigned long long iblnkerrdelta; scalar_t__ ibdeltainprog; } ;
struct TYPE_4__ {unsigned long long ibsymsnap; unsigned long long iblnkerrsnap; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  QIBPORTCNTR_BADFORMAT 194 
#define  QIBPORTCNTR_ERRICRC 193 
#define  QIBPORTCNTR_ERRLINK 192 
#define  QIBPORTCNTR_ERRLPCRC 191 
#define  QIBPORTCNTR_ERRPKEY 190 
#define  QIBPORTCNTR_ERRVCRC 189 
#define  QIBPORTCNTR_ERR_RLEN 188 
#define  QIBPORTCNTR_EXCESSBUFOVFL 187 
#define  QIBPORTCNTR_IBLINKDOWN 186 
#define  QIBPORTCNTR_IBLINKERRRECOV 185 
#define  QIBPORTCNTR_IBSYMBOLERR 184 
#define  QIBPORTCNTR_INVALIDRLEN 183 
#define  QIBPORTCNTR_KHDROVFL 182 
#define  QIBPORTCNTR_LLI 181 
#define  QIBPORTCNTR_PKTRCV 180 
#define  QIBPORTCNTR_PKTSEND 179 
#define  QIBPORTCNTR_PSINTERVAL 178 
#define  QIBPORTCNTR_PSRCVDATA 177 
#define  QIBPORTCNTR_PSRCVPKTS 176 
#define  QIBPORTCNTR_PSSTART 175 
#define  QIBPORTCNTR_PSSTAT 174 
#define  QIBPORTCNTR_PSXMITDATA 173 
#define  QIBPORTCNTR_PSXMITPKTS 172 
#define  QIBPORTCNTR_PSXMITWAIT 171 
#define  QIBPORTCNTR_RCVEBP 170 
#define  QIBPORTCNTR_RCVOVFL 169 
#define  QIBPORTCNTR_RXDROPPKT 168 
#define  QIBPORTCNTR_RXLOCALPHYERR 167 
#define  QIBPORTCNTR_RXVLERR 166 
#define  QIBPORTCNTR_SENDSTALL 165 
#define  QIBPORTCNTR_UNSUPVL 164 
#define  QIBPORTCNTR_VL15PKTDROP 163 
#define  QIBPORTCNTR_WORDRCV 162 
#define  QIBPORTCNTR_WORDSEND 161 
#define  cr_badformat 160 
#define  cr_err_rlen 159 
#define  cr_erricrc 158 
#define  cr_errlink 157 
#define  cr_errlpcrc 156 
#define  cr_errpkey 155 
#define  cr_errvcrc 154 
#define  cr_excessbufferovfl 153 
#define  cr_iblinkdown 152 
#define  cr_iblinkerrrecov 151 
#define  cr_ibsymbolerr 150 
#define  cr_invalidrlen 149 
#define  cr_locallinkintegrityerr 148 
#define  cr_pktrcv 147 
#define  cr_pktsend 146 
 int cr_portovfl ; 
#define  cr_psinterval 145 
#define  cr_psrcvdatacount 144 
#define  cr_psrcvpktscount 143 
#define  cr_psstart 142 
#define  cr_psstat 141 
#define  cr_psxmitdatacount 140 
#define  cr_psxmitpktscount 139 
#define  cr_psxmitwaitcount 138 
#define  cr_rcvebp 137 
#define  cr_rcvovfl 136 
#define  cr_rxdroppkt 135 
#define  cr_rxotherlocalphyerr 134 
#define  cr_rxvlerr 133 
#define  cr_sendstall 132 
#define  cr_txunsupvl 131 
#define  cr_vl15droppedpkt 130 
#define  cr_wordrcv 129 
#define  cr_wordsend 128 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,size_t) ; 
 unsigned long long read_7220_creg (struct qib_devdata*,int) ; 
 unsigned long long read_7220_creg32 (struct qib_devdata*,int) ; 

__attribute__((used)) static u64 qib_portcntr_7220(struct qib_pportdata *ppd, u32 reg)
{
	u64 ret = 0ULL;
	struct qib_devdata *dd = ppd->dd;
	u16 creg;
	/* 0xffff for unimplemented or synthesized counters */
	static const u16 xlator[] = {
		[QIBPORTCNTR_PKTSEND] = cr_pktsend,
		[QIBPORTCNTR_WORDSEND] = cr_wordsend,
		[QIBPORTCNTR_PSXMITDATA] = cr_psxmitdatacount,
		[QIBPORTCNTR_PSXMITPKTS] = cr_psxmitpktscount,
		[QIBPORTCNTR_PSXMITWAIT] = cr_psxmitwaitcount,
		[QIBPORTCNTR_SENDSTALL] = cr_sendstall,
		[QIBPORTCNTR_PKTRCV] = cr_pktrcv,
		[QIBPORTCNTR_PSRCVDATA] = cr_psrcvdatacount,
		[QIBPORTCNTR_PSRCVPKTS] = cr_psrcvpktscount,
		[QIBPORTCNTR_RCVEBP] = cr_rcvebp,
		[QIBPORTCNTR_RCVOVFL] = cr_rcvovfl,
		[QIBPORTCNTR_WORDRCV] = cr_wordrcv,
		[QIBPORTCNTR_RXDROPPKT] = cr_rxdroppkt,
		[QIBPORTCNTR_RXLOCALPHYERR] = cr_rxotherlocalphyerr,
		[QIBPORTCNTR_RXVLERR] = cr_rxvlerr,
		[QIBPORTCNTR_ERRICRC] = cr_erricrc,
		[QIBPORTCNTR_ERRVCRC] = cr_errvcrc,
		[QIBPORTCNTR_ERRLPCRC] = cr_errlpcrc,
		[QIBPORTCNTR_BADFORMAT] = cr_badformat,
		[QIBPORTCNTR_ERR_RLEN] = cr_err_rlen,
		[QIBPORTCNTR_IBSYMBOLERR] = cr_ibsymbolerr,
		[QIBPORTCNTR_INVALIDRLEN] = cr_invalidrlen,
		[QIBPORTCNTR_UNSUPVL] = cr_txunsupvl,
		[QIBPORTCNTR_EXCESSBUFOVFL] = cr_excessbufferovfl,
		[QIBPORTCNTR_ERRLINK] = cr_errlink,
		[QIBPORTCNTR_IBLINKDOWN] = cr_iblinkdown,
		[QIBPORTCNTR_IBLINKERRRECOV] = cr_iblinkerrrecov,
		[QIBPORTCNTR_LLI] = cr_locallinkintegrityerr,
		[QIBPORTCNTR_PSINTERVAL] = cr_psinterval,
		[QIBPORTCNTR_PSSTART] = cr_psstart,
		[QIBPORTCNTR_PSSTAT] = cr_psstat,
		[QIBPORTCNTR_VL15PKTDROP] = cr_vl15droppedpkt,
		[QIBPORTCNTR_ERRPKEY] = cr_errpkey,
		[QIBPORTCNTR_KHDROVFL] = 0xffff,
	};

	if (reg >= ARRAY_SIZE(xlator)) {
		qib_devinfo(ppd->dd->pcidev,
			 "Unimplemented portcounter %u\n", reg);
		goto done;
	}
	creg = xlator[reg];

	if (reg == QIBPORTCNTR_KHDROVFL) {
		int i;

		/* sum over all kernel contexts */
		for (i = 0; i < dd->first_user_ctxt; i++)
			ret += read_7220_creg32(dd, cr_portovfl + i);
	}
	if (creg == 0xffff)
		goto done;

	/*
	 * only fast incrementing counters are 64bit; use 32 bit reads to
	 * avoid two independent reads when on opteron
	 */
	if ((creg == cr_wordsend || creg == cr_wordrcv ||
	     creg == cr_pktsend || creg == cr_pktrcv))
		ret = read_7220_creg(dd, creg);
	else
		ret = read_7220_creg32(dd, creg);
	if (creg == cr_ibsymbolerr) {
		if (dd->pport->cpspec->ibdeltainprog)
			ret -= ret - ppd->cpspec->ibsymsnap;
		ret -= dd->pport->cpspec->ibsymdelta;
	} else if (creg == cr_iblinkerrrecov) {
		if (dd->pport->cpspec->ibdeltainprog)
			ret -= ret - ppd->cpspec->iblnkerrsnap;
		ret -= dd->pport->cpspec->iblnkerrdelta;
	}
done:
	return ret;
}