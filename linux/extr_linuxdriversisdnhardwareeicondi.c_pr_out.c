#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_34__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  size_t byte ;
struct TYPE_40__ {size_t (* ram_inw ) (TYPE_5__*,int /*<<< orphan*/ *) ;size_t* IdTypeTable; size_t* FlowControlIdTable; int* FlowControlSkipTable; size_t (* ram_in ) (TYPE_5__*,int /*<<< orphan*/ *) ;size_t* IdTable; int /*<<< orphan*/  (* ram_out ) (TYPE_5__*,int /*<<< orphan*/ *,size_t) ;int /*<<< orphan*/  (* ram_outw ) (TYPE_5__*,int /*<<< orphan*/ *,size_t) ;int /*<<< orphan*/ * misc_flags_table; int /*<<< orphan*/  (* ram_out_buffer ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_39__ {int PLength; int /*<<< orphan*/ * P; } ;
struct TYPE_38__ {size_t Req; size_t Id; size_t ReqCh; int XCurrent; int XNum; size_t XOffset; size_t MInd; size_t No; int /*<<< orphan*/  More; } ;
struct TYPE_37__ {int /*<<< orphan*/  ReqInput; int /*<<< orphan*/  NextReq; int /*<<< orphan*/ * B; } ;
struct TYPE_35__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * P; } ;
struct TYPE_36__ {int /*<<< orphan*/  next; int /*<<< orphan*/  Reference; int /*<<< orphan*/  Req; int /*<<< orphan*/  ReqCh; int /*<<< orphan*/  ReqId; TYPE_1__ XBuffer; } ;
typedef  TYPE_2__ REQ ;
typedef  TYPE_3__ ENTITY ;
typedef  TYPE_4__ BUFFERS ;
typedef  TYPE_5__ ADAPTER ;

/* Variables and functions */
 size_t BLLC_ID ; 
 int /*<<< orphan*/  DIVA_MISC_FLAGS_REMOVE_PENDING ; 
 size_t LL_MDATA ; 
 size_t MAN_ID ; 
 size_t NL_ID ; 
 size_t N_MDATA ; 
 TYPE_34__* PR_RAM ; 
 int /*<<< orphan*/  PTR_P (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* PTR_X (TYPE_5__*,TYPE_3__*) ; 
 size_t REMOVE ; 
 size_t TASK_ID ; 
 scalar_t__ UREMOVE ; 
 int /*<<< orphan*/  XDI_A_NR (TYPE_5__*) ; 
 int /*<<< orphan*/  XMOREF ; 
 int /*<<< orphan*/  assign_queue (TYPE_5__*,size_t,size_t) ; 
 int /*<<< orphan*/  dbug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  dtrc (int /*<<< orphan*/ ) ; 
 TYPE_3__* entity_ptr (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  free_entity (TYPE_5__*,size_t) ; 
 size_t look_req (TYPE_5__*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  next_req (TYPE_5__*) ; 
 size_t pr_ready (TYPE_5__*) ; 
 int /*<<< orphan*/  req_queue (TYPE_5__*,size_t) ; 
 size_t stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 size_t stub11 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 size_t stub13 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub6 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub7 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub8 (TYPE_5__*,int /*<<< orphan*/ *,size_t) ; 
 size_t stub9 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdi_xlog_request (int /*<<< orphan*/ ,int,size_t,size_t,size_t) ; 

void pr_out(ADAPTER *a)
{
	byte e_no;
	ENTITY *this = NULL;
	BUFFERS *X;
	word length;
	word i;
	word clength;
	REQ *ReqOut;
	byte more;
	byte ReadyCount;
	byte ReqCount;
	byte Id;
	dtrc(dprintf("pr_out"));
	/* while a request is pending ...                           */
	e_no = look_req(a);
	if (!e_no)
	{
		dtrc(dprintf("no_req"));
		return;
	}
	ReadyCount = pr_ready(a);
	if (!ReadyCount)
	{
		dtrc(dprintf("not_ready"));
		return;
	}
	ReqCount = 0;
	while (e_no && ReadyCount) {
		next_req(a);
		this = entity_ptr(a, e_no);
#ifdef USE_EXTENDED_DEBUGS
		if (!this)
		{
			DBG_FTL(("XDI: [%02x] !A%d ==> NULL entity ptr - try to ignore",
				 xdi_xlog_sec++, (int)((ISDN_ADAPTER *)a->io)->ANum))
				e_no = look_req(a);
			ReadyCount--;
			continue;
		}
		{
			DBG_TRC((">A%d Id=0x%x Req=0x%x", ((ISDN_ADAPTER *)a->io)->ANum, this->Id, this->Req))
				}
#else
		dbug(dprintf("out:Req=%x,Id=%x,Ch=%x", this->Req, this->Id, this->ReqCh));
#endif
		/* get address of next available request buffer             */
		ReqOut = (REQ *)&PR_RAM->B[a->ram_inw(a, &PR_RAM->NextReq)];
#if defined(DIVA_ISTREAM)
		if (!(a->tx_stream[this->Id]   &&
		      this->Req == N_DATA)) {
#endif
			/* now copy the data from the current data buffer into the  */
			/* adapters request buffer                                  */
			length = 0;
			i = this->XCurrent;
			X = PTR_X(a, this);
			while (i < this->XNum && length < 270) {
				clength = min((word)(270 - length), (word)(X[i].PLength-this->XOffset));
				a->ram_out_buffer(a,
						  &ReqOut->XBuffer.P[length],
						  PTR_P(a, this, &X[i].P[this->XOffset]),
						  clength);
				length += clength;
				this->XOffset += clength;
				if (this->XOffset == X[i].PLength) {
					this->XCurrent = (byte)++i;
					this->XOffset = 0;
				}
			}
#if defined(DIVA_ISTREAM)
		} else { /* Use CMA extension in order to transfer data to the card */
			i = this->XCurrent;
			X = PTR_X(a, this);
			while (i < this->XNum) {
				diva_istream_write(a,
						   this->Id,
						   PTR_P(a, this, &X[i].P[0]),
						   X[i].PLength,
						   ((i + 1) == this->XNum),
						   0, 0);
				this->XCurrent = (byte)++i;
			}
			length = 0;
		}
#endif
		a->ram_outw(a, &ReqOut->XBuffer.length, length);
		a->ram_out(a, &ReqOut->ReqId, this->Id);
		a->ram_out(a, &ReqOut->ReqCh, this->ReqCh);
		/* if it's a specific request (no ASSIGN) ...                */
		if (this->Id & 0x1f) {
			/* if buffers are left in the list of data buffers do       */
			/* do chaining (LL_MDATA, N_MDATA)                          */
			this->More++;
			if (i < this->XNum && this->MInd) {
				xdi_xlog_request(XDI_A_NR(a), this->Id, this->ReqCh, this->MInd,
						 a->IdTypeTable[this->No]);
				a->ram_out(a, &ReqOut->Req, this->MInd);
				more = true;
			}
			else {
				xdi_xlog_request(XDI_A_NR(a), this->Id, this->ReqCh, this->Req,
						 a->IdTypeTable[this->No]);
				this->More |= XMOREF;
				a->ram_out(a, &ReqOut->Req, this->Req);
				more = false;
				if (a->FlowControlIdTable[this->ReqCh] == this->Id)
					a->FlowControlSkipTable[this->ReqCh] = true;
				/*
				  Note that remove request was sent to the card
				*/
				if (this->Req == REMOVE) {
					a->misc_flags_table[e_no] |= DIVA_MISC_FLAGS_REMOVE_PENDING;
				}
			}
			/* if we did chaining, this entity is put back into the     */
			/* request queue                                            */
			if (more) {
				req_queue(a, this->No);
			}
		}
		/* else it's a ASSIGN                                       */
		else {
			/* save the request code used for buffer chaining           */
			this->MInd = 0;
			if (this->Id == BLLC_ID) this->MInd = LL_MDATA;
			if (this->Id == NL_ID ||
			    this->Id == TASK_ID ||
			    this->Id == MAN_ID
				) this->MInd = N_MDATA;
			/* send the ASSIGN                                          */
			a->IdTypeTable[this->No] = this->Id;
			xdi_xlog_request(XDI_A_NR(a), this->Id, this->ReqCh, this->Req, this->Id);
			this->More |= XMOREF;
			a->ram_out(a, &ReqOut->Req, this->Req);
			/* save the reference of the ASSIGN                         */
			assign_queue(a, this->No, a->ram_inw(a, &ReqOut->Reference));
		}
		a->ram_outw(a, &PR_RAM->NextReq, a->ram_inw(a, &ReqOut->next));
		ReadyCount--;
		ReqCount++;
		e_no = look_req(a);
	}
	/* send the filled request buffers to the ISDN adapter      */
	a->ram_out(a, &PR_RAM->ReqInput,
		   (byte)(a->ram_in(a, &PR_RAM->ReqInput) + ReqCount));
	/* if it is a 'unreturncoded' UREMOVE request, remove the  */
	/* Id from our table after sending the request             */
	if (this && (this->Req == UREMOVE) && this->Id) {
		Id = this->Id;
		e_no = a->IdTable[Id];
		free_entity(a, e_no);
		for (i = 0; i < 256; i++)
		{
			if (a->FlowControlIdTable[i] == Id)
				a->FlowControlIdTable[i] = 0;
		}
		a->IdTable[Id] = 0;
		this->Id = 0;
	}
}