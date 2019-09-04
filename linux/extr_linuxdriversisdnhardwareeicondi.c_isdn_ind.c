#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  size_t byte ;
struct TYPE_26__ {size_t (* ram_inw ) (TYPE_4__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * IdTypeTable; int /*<<< orphan*/  (* ram_in_buffer ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ;scalar_t__* IdTable; int /*<<< orphan*/  (* ram_look_ahead ) (TYPE_4__*,TYPE_1__*,TYPE_2__*) ;} ;
struct TYPE_25__ {size_t PLength; int /*<<< orphan*/ * P; } ;
struct TYPE_24__ {size_t IndCh; size_t No; int RCurrent; size_t MInd; int complete; size_t Ind; size_t RLength; size_t RNum; int RNR; size_t ROffset; } ;
struct TYPE_23__ {int /*<<< orphan*/ * P; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ PBUFFER ;
typedef  TYPE_2__ ENTITY ;
typedef  TYPE_3__ BUFFERS ;
typedef  TYPE_4__ ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PTR_P (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* PTR_R (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  XDI_A_NR (TYPE_4__*) ; 
 int /*<<< orphan*/  dbug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,size_t,size_t,size_t) ; 
 TYPE_2__* entity_ptr (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_1__*,TYPE_2__*) ; 
 size_t stub2 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 size_t stub3 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xdi_xlog_ind (int /*<<< orphan*/ ,size_t,size_t,size_t,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static byte isdn_ind(ADAPTER *a,
		     byte Ind,
		     byte Id,
		     byte Ch,
		     PBUFFER *RBuffer,
		     byte MInd,
		     word MLength)
{
	ENTITY *this;
	word clength;
	word offset;
	BUFFERS *R;
	byte *cma = NULL;
#ifdef USE_EXTENDED_DEBUGS
	{
		DBG_TRC(("<A%d Id=0x%x Ind=0x%x", ((ISDN_ADAPTER *)a->io)->ANum, Id, Ind))
			}
#else
	dbug(dprintf("isdn_ind(Ind=%x,Id=%x,Ch=%x)", Ind, Id, Ch));
#endif
	if (a->IdTable[Id]) {
		this = entity_ptr(a, a->IdTable[Id]);
		this->IndCh = Ch;
		xdi_xlog_ind(XDI_A_NR(a), Id, Ch, Ind,
			     0/* rnr_valid */, 0 /* rnr */, a->IdTypeTable[this->No]);
		/* if the Receive More flag is not yet set, this is the     */
		/* first buffer of the packet                               */
		if (this->RCurrent == 0xff) {
			/* check for receive buffer chaining                        */
			if (Ind == this->MInd) {
				this->complete = 0;
				this->Ind = MInd;
			}
			else {
				this->complete = 1;
				this->Ind = Ind;
			}
			/* call the application callback function for the receive   */
			/* look ahead                                               */
			this->RLength = MLength;
#if defined(DIVA_ISTREAM)
			if ((a->rx_stream[this->Id] ||
			     (a->misc_flags_table[this->No] & DIVA_MISC_FLAGS_RX_DMA)) &&
			    ((Ind == N_DATA) ||
			     (a->protocol_capabilities & PROTCAP_CMA_ALLPR))) {
				PISDN_ADAPTER IoAdapter = (PISDN_ADAPTER)a->io;
				if (a->misc_flags_table[this->No] & DIVA_MISC_FLAGS_RX_DMA) {
#if defined(DIVA_IDI_RX_DMA)
					dword d;
					diva_get_dma_map_entry(\
						(struct _diva_dma_map_entry *)IoAdapter->dma_map,
						(int)a->rx_stream[this->Id], (void **)&cma, &d);
#else
					cma = &a->stream_buffer[0];
					cma[0] = cma[1] = cma[2] = cma[3] = 0;
#endif
					this->RLength = MLength = (word)*(dword *)cma;
					cma += 4;
				} else {
					int final = 0;
					cma = &a->stream_buffer[0];
					this->RLength = MLength = (word)diva_istream_read(a,
											  Id,
											  cma,
											  sizeof(a->stream_buffer),
											  &final, NULL, NULL);
				}
				IoAdapter->RBuffer.length = min(MLength, (word)270);
				if (IoAdapter->RBuffer.length != MLength) {
					this->complete = 0;
				} else {
					this->complete = 1;
				}
				memcpy(IoAdapter->RBuffer.P, cma, IoAdapter->RBuffer.length);
				this->RBuffer = (DBUFFER *)&IoAdapter->RBuffer;
			}
#endif
			if (!cma) {
				a->ram_look_ahead(a, RBuffer, this);
			}
			this->RNum = 0;
			CALLBACK(a, this);
			/* map entity ptr, selector could be re-mapped by call to   */
			/* IDI from within callback                                 */
			this = entity_ptr(a, a->IdTable[Id]);
			xdi_xlog_ind(XDI_A_NR(a), Id, Ch, Ind,
				     1/* rnr_valid */, this->RNR/* rnr */, a->IdTypeTable[this->No]);
			/* check for RNR                                            */
			if (this->RNR == 1) {
				this->RNR = 0;
				return 1;
			}
			/* if no buffers are provided by the application, the       */
			/* application want to copy the data itself including       */
			/* N_MDATA/LL_MDATA chaining                                */
			if (!this->RNR && !this->RNum) {
				xdi_xlog_ind(XDI_A_NR(a), Id, Ch, Ind,
					     2/* rnr_valid */, 0/* rnr */, a->IdTypeTable[this->No]);
				return 0;
			}
			/* if there is no RNR, set the More flag                    */
			this->RCurrent = 0;
			this->ROffset = 0;
		}
		if (this->RNR == 2) {
			if (Ind != this->MInd) {
				this->RCurrent = 0xff;
				this->RNR = 0;
			}
			return 0;
		}
		/* if we have received buffers from the application, copy   */
		/* the data into these buffers                              */
		offset = 0;
		R = PTR_R(a, this);
		do {
			if (this->ROffset == R[this->RCurrent].PLength) {
				this->ROffset = 0;
				this->RCurrent++;
			}
			if (cma) {
				clength = min(MLength, (word)(R[this->RCurrent].PLength-this->ROffset));
			} else {
				clength = min(a->ram_inw(a, &RBuffer->length)-offset,
					      R[this->RCurrent].PLength-this->ROffset);
			}
			if (R[this->RCurrent].P) {
				if (cma) {
					memcpy(PTR_P(a, this, &R[this->RCurrent].P[this->ROffset]),
					       &cma[offset],
					       clength);
				} else {
					a->ram_in_buffer(a,
							 &RBuffer->P[offset],
							 PTR_P(a, this, &R[this->RCurrent].P[this->ROffset]),
							 clength);
				}
			}
			offset += clength;
			this->ROffset += clength;
			if (cma) {
				if (offset >= MLength) {
					break;
				}
				continue;
			}
		} while (offset < (a->ram_inw(a, &RBuffer->length)));
		/* if it's the last buffer of the packet, call the          */
		/* application callback function for the receive complete   */
		/* call                                                     */
		if (Ind != this->MInd) {
			R[this->RCurrent].PLength = this->ROffset;
			if (this->ROffset) this->RCurrent++;
			this->RNum = this->RCurrent;
			this->RCurrent = 0xff;
			this->Ind = Ind;
			this->complete = 2;
			xdi_xlog_ind(XDI_A_NR(a), Id, Ch, Ind,
				     3/* rnr_valid */, 0/* rnr */, a->IdTypeTable[this->No]);
			CALLBACK(a, this);
		}
		return 0;
	}
	return 2;
}