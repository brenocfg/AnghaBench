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
typedef  int u64 ;
struct qib_devdata {int /*<<< orphan*/  pport; } ;

/* Variables and functions */
 int ERR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HardwareErr ; 
 int /*<<< orphan*/  IBStatusChanged ; 
 int /*<<< orphan*/  InvalidAddrErr ; 
 int /*<<< orphan*/  InvalidEEPCmd ; 
 int QLOGIC_IB_E_PKTERRS ; 
 int QLOGIC_IB_E_SDMAERRS ; 
 int /*<<< orphan*/  RcvBadTidErr ; 
 int /*<<< orphan*/  RcvBadVersionErr ; 
 int /*<<< orphan*/  RcvEBPErr ; 
 int /*<<< orphan*/  RcvEgrFullErr ; 
 int /*<<< orphan*/  RcvFormatErr ; 
 int /*<<< orphan*/  RcvHdrErr ; 
 int /*<<< orphan*/  RcvHdrFullErr ; 
 int /*<<< orphan*/  RcvHdrLenErr ; 
 int /*<<< orphan*/  RcvIBFlowErr ; 
 int /*<<< orphan*/  RcvIBLostLinkErr ; 
 int /*<<< orphan*/  RcvICRCErr ; 
 int /*<<< orphan*/  RcvLongPktLenErr ; 
 int /*<<< orphan*/  RcvMaxPktLenErr ; 
 int /*<<< orphan*/  RcvMinPktLenErr ; 
 int /*<<< orphan*/  RcvUnexpectedCharErr ; 
 int /*<<< orphan*/  RcvUnsupportedVLErr ; 
 int /*<<< orphan*/  RcvVCRCErr ; 
 int /*<<< orphan*/  ResetNegated ; 
 int /*<<< orphan*/  SendDroppedSmpPktErr ; 
 int /*<<< orphan*/  SendMaxPktLenErr ; 
 int /*<<< orphan*/  SendMinPktLenErr ; 
 int /*<<< orphan*/  SendPioArmLaunchErr ; 
 int /*<<< orphan*/  SendSpecialTriggerErr ; 
 int /*<<< orphan*/  SendUnderRunErr ; 
 int /*<<< orphan*/  SendUnexpectedPktNumErr ; 
 int /*<<< orphan*/  SendUnsupportedVLErr ; 
 int /*<<< orphan*/  qib_decode_7220_sdma_errs (int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static int qib_decode_7220_err(struct qib_devdata *dd, char *buf, size_t blen,
			       u64 err)
{
	int iserr = 1;

	*buf = '\0';
	if (err & QLOGIC_IB_E_PKTERRS) {
		if (!(err & ~QLOGIC_IB_E_PKTERRS))
			iserr = 0;
		if ((err & ERR_MASK(RcvICRCErr)) &&
		    !(err & (ERR_MASK(RcvVCRCErr) | ERR_MASK(RcvEBPErr))))
			strlcat(buf, "CRC ", blen);
		if (!iserr)
			goto done;
	}
	if (err & ERR_MASK(RcvHdrLenErr))
		strlcat(buf, "rhdrlen ", blen);
	if (err & ERR_MASK(RcvBadTidErr))
		strlcat(buf, "rbadtid ", blen);
	if (err & ERR_MASK(RcvBadVersionErr))
		strlcat(buf, "rbadversion ", blen);
	if (err & ERR_MASK(RcvHdrErr))
		strlcat(buf, "rhdr ", blen);
	if (err & ERR_MASK(SendSpecialTriggerErr))
		strlcat(buf, "sendspecialtrigger ", blen);
	if (err & ERR_MASK(RcvLongPktLenErr))
		strlcat(buf, "rlongpktlen ", blen);
	if (err & ERR_MASK(RcvMaxPktLenErr))
		strlcat(buf, "rmaxpktlen ", blen);
	if (err & ERR_MASK(RcvMinPktLenErr))
		strlcat(buf, "rminpktlen ", blen);
	if (err & ERR_MASK(SendMinPktLenErr))
		strlcat(buf, "sminpktlen ", blen);
	if (err & ERR_MASK(RcvFormatErr))
		strlcat(buf, "rformaterr ", blen);
	if (err & ERR_MASK(RcvUnsupportedVLErr))
		strlcat(buf, "runsupvl ", blen);
	if (err & ERR_MASK(RcvUnexpectedCharErr))
		strlcat(buf, "runexpchar ", blen);
	if (err & ERR_MASK(RcvIBFlowErr))
		strlcat(buf, "ribflow ", blen);
	if (err & ERR_MASK(SendUnderRunErr))
		strlcat(buf, "sunderrun ", blen);
	if (err & ERR_MASK(SendPioArmLaunchErr))
		strlcat(buf, "spioarmlaunch ", blen);
	if (err & ERR_MASK(SendUnexpectedPktNumErr))
		strlcat(buf, "sunexperrpktnum ", blen);
	if (err & ERR_MASK(SendDroppedSmpPktErr))
		strlcat(buf, "sdroppedsmppkt ", blen);
	if (err & ERR_MASK(SendMaxPktLenErr))
		strlcat(buf, "smaxpktlen ", blen);
	if (err & ERR_MASK(SendUnsupportedVLErr))
		strlcat(buf, "sunsupVL ", blen);
	if (err & ERR_MASK(InvalidAddrErr))
		strlcat(buf, "invalidaddr ", blen);
	if (err & ERR_MASK(RcvEgrFullErr))
		strlcat(buf, "rcvegrfull ", blen);
	if (err & ERR_MASK(RcvHdrFullErr))
		strlcat(buf, "rcvhdrfull ", blen);
	if (err & ERR_MASK(IBStatusChanged))
		strlcat(buf, "ibcstatuschg ", blen);
	if (err & ERR_MASK(RcvIBLostLinkErr))
		strlcat(buf, "riblostlink ", blen);
	if (err & ERR_MASK(HardwareErr))
		strlcat(buf, "hardware ", blen);
	if (err & ERR_MASK(ResetNegated))
		strlcat(buf, "reset ", blen);
	if (err & QLOGIC_IB_E_SDMAERRS)
		qib_decode_7220_sdma_errs(dd->pport, err, buf, blen);
	if (err & ERR_MASK(InvalidEEPCmd))
		strlcat(buf, "invalideepromcmd ", blen);
done:
	return iserr;
}