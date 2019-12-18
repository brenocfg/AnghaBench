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
typedef  int uint16_t ;
struct scsi_cmnd {int sc_data_direction; } ;

/* Variables and functions */
 int BIT_5 ; 
 int BIT_6 ; 
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 

__attribute__((used)) static inline uint16_t
qla1280_data_direction(struct scsi_cmnd *cmnd)
{
	switch(cmnd->sc_data_direction) {
	case DMA_FROM_DEVICE:
		return BIT_5;
	case DMA_TO_DEVICE:
		return BIT_6;
	case DMA_BIDIRECTIONAL:
		return BIT_5 | BIT_6;
	/*
	 * We could BUG() on default here if one of the four cases aren't
	 * met, but then again if we receive something like that from the
	 * SCSI layer we have more serious problems. This shuts up GCC.
	 */
	case DMA_NONE:
	default:
		return 0;
	}
}