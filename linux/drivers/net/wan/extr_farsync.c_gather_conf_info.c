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
struct fstioc_info {scalar_t__ type; scalar_t__ state; int index; int valid; int cableStatus; void* alarmIndicationSignal; void* receiveRemoteAlarm; void* lossOfSignal; void* lineAttenuation; void* crcErrorCount; void* codeViolationCount; void* framingErrorCount; void* receiveBufferDelay; void* idleCode; void* losThreshold; void* startingSlot; void* rxBufferMode; void* txBufferMode; void* range; void* loopMode; void* equalizer; void* lineBuildOut; void* coding; void* interface; void* structure; void* framing; void* clockSource; void* lineSpeed; void* smcFirmwareVersion; void* cardMode; void* clockStatus; void* v24OpSts; void* v24IpSts; void* invertClock; void* internalClock; void* lineInterface; int /*<<< orphan*/  debug; int /*<<< orphan*/  proto; int /*<<< orphan*/  nports; int /*<<< orphan*/  kernelVersion; } ;
struct fst_port_info {int index; } ;
struct fst_card_info {scalar_t__ type; scalar_t__ state; scalar_t__ family; int /*<<< orphan*/  nports; } ;
struct TYPE_6__ {int /*<<< orphan*/  invertClock; int /*<<< orphan*/  lineSpeed; int /*<<< orphan*/  internalClock; int /*<<< orphan*/  lineInterface; } ;
struct TYPE_5__ {int /*<<< orphan*/  idleCode; int /*<<< orphan*/  enableIdleCode; int /*<<< orphan*/  losThreshold; int /*<<< orphan*/  startingSlot; int /*<<< orphan*/  rxBufferMode; int /*<<< orphan*/  txBufferMode; int /*<<< orphan*/  range; int /*<<< orphan*/  loopMode; int /*<<< orphan*/  equalizer; int /*<<< orphan*/  lineBuildOut; int /*<<< orphan*/  coding; int /*<<< orphan*/  interface; int /*<<< orphan*/  structure; int /*<<< orphan*/  framing; int /*<<< orphan*/  clocking; int /*<<< orphan*/  dataRate; } ;
struct TYPE_4__ {int /*<<< orphan*/  alarmIndicationSignal; int /*<<< orphan*/  receiveRemoteAlarm; int /*<<< orphan*/  lossOfSignal; int /*<<< orphan*/  lineAttenuation; int /*<<< orphan*/  crcErrorCount; int /*<<< orphan*/  codeViolationCount; int /*<<< orphan*/  framingErrorCount; int /*<<< orphan*/  receiveBufferDelay; } ;

/* Variables and functions */
 int FSTVAL_ALL ; 
 int FSTVAL_CARD ; 
 int FSTVAL_DEBUG ; 
 scalar_t__ FST_FAMILY_TXU ; 
 int /*<<< orphan*/  FST_GEN_HDLC ; 
 void* FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 void* FST_RDL (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 void* FST_RDW (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ FST_RUNNING ; 
 scalar_t__ FST_TYPE_TE1 ; 
 int /*<<< orphan*/  LINUX_VERSION_CODE ; 
 int /*<<< orphan*/  cableStatus ; 
 int /*<<< orphan*/  cardMode ; 
 int /*<<< orphan*/ * clockStatus ; 
 int /*<<< orphan*/  fst_debug_mask ; 
 int /*<<< orphan*/  memset (struct fstioc_info*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* portConfig ; 
 int /*<<< orphan*/  smcFirmwareVersion ; 
 TYPE_2__ suConfig ; 
 TYPE_1__ suStatus ; 
 int /*<<< orphan*/ * v24IpSts ; 
 int /*<<< orphan*/ * v24OpSts ; 

__attribute__((used)) static void
gather_conf_info(struct fst_card_info *card, struct fst_port_info *port,
		 struct fstioc_info *info)
{
	int i;

	memset(info, 0, sizeof (struct fstioc_info));

	i = port->index;
	info->kernelVersion = LINUX_VERSION_CODE;
	info->nports = card->nports;
	info->type = card->type;
	info->state = card->state;
	info->proto = FST_GEN_HDLC;
	info->index = i;
#if FST_DEBUG
	info->debug = fst_debug_mask;
#endif

	/* Only mark information as valid if card is running.
	 * Copy the data anyway in case it is useful for diagnostics
	 */
	info->valid = ((card->state == FST_RUNNING) ? FSTVAL_ALL : FSTVAL_CARD)
#if FST_DEBUG
	    | FSTVAL_DEBUG
#endif
	    ;

	info->lineInterface = FST_RDW(card, portConfig[i].lineInterface);
	info->internalClock = FST_RDB(card, portConfig[i].internalClock);
	info->lineSpeed = FST_RDL(card, portConfig[i].lineSpeed);
	info->invertClock = FST_RDB(card, portConfig[i].invertClock);
	info->v24IpSts = FST_RDL(card, v24IpSts[i]);
	info->v24OpSts = FST_RDL(card, v24OpSts[i]);
	info->clockStatus = FST_RDW(card, clockStatus[i]);
	info->cableStatus = FST_RDW(card, cableStatus);
	info->cardMode = FST_RDW(card, cardMode);
	info->smcFirmwareVersion = FST_RDL(card, smcFirmwareVersion);

	/*
	 * The T2U can report cable presence for both A or B
	 * in bits 0 and 1 of cableStatus.  See which port we are and 
	 * do the mapping.
	 */
	if (card->family == FST_FAMILY_TXU) {
		if (port->index == 0) {
			/*
			 * Port A
			 */
			info->cableStatus = info->cableStatus & 1;
		} else {
			/*
			 * Port B
			 */
			info->cableStatus = info->cableStatus >> 1;
			info->cableStatus = info->cableStatus & 1;
		}
	}
	/*
	 * Some additional bits if we are TE1
	 */
	if (card->type == FST_TYPE_TE1) {
		info->lineSpeed = FST_RDL(card, suConfig.dataRate);
		info->clockSource = FST_RDB(card, suConfig.clocking);
		info->framing = FST_RDB(card, suConfig.framing);
		info->structure = FST_RDB(card, suConfig.structure);
		info->interface = FST_RDB(card, suConfig.interface);
		info->coding = FST_RDB(card, suConfig.coding);
		info->lineBuildOut = FST_RDB(card, suConfig.lineBuildOut);
		info->equalizer = FST_RDB(card, suConfig.equalizer);
		info->loopMode = FST_RDB(card, suConfig.loopMode);
		info->range = FST_RDB(card, suConfig.range);
		info->txBufferMode = FST_RDB(card, suConfig.txBufferMode);
		info->rxBufferMode = FST_RDB(card, suConfig.rxBufferMode);
		info->startingSlot = FST_RDB(card, suConfig.startingSlot);
		info->losThreshold = FST_RDB(card, suConfig.losThreshold);
		if (FST_RDB(card, suConfig.enableIdleCode))
			info->idleCode = FST_RDB(card, suConfig.idleCode);
		else
			info->idleCode = 0;
		info->receiveBufferDelay =
		    FST_RDL(card, suStatus.receiveBufferDelay);
		info->framingErrorCount =
		    FST_RDL(card, suStatus.framingErrorCount);
		info->codeViolationCount =
		    FST_RDL(card, suStatus.codeViolationCount);
		info->crcErrorCount = FST_RDL(card, suStatus.crcErrorCount);
		info->lineAttenuation = FST_RDL(card, suStatus.lineAttenuation);
		info->lossOfSignal = FST_RDB(card, suStatus.lossOfSignal);
		info->receiveRemoteAlarm =
		    FST_RDB(card, suStatus.receiveRemoteAlarm);
		info->alarmIndicationSignal =
		    FST_RDB(card, suStatus.alarmIndicationSignal);
	}
}