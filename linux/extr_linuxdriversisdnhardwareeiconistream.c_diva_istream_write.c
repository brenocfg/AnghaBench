#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  dword ;
typedef  char byte ;
struct TYPE_5__ {scalar_t__* tx_pos; scalar_t__* tx_stream; int /*<<< orphan*/  (* ram_out_dw ) (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* ram_out_buffer ) (TYPE_1__*,void*,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ram_in_dw ) (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_DFIFO_DATA_SZ ; 
 char DIVA_DFIFO_LAST ; 
 char DIVA_DFIFO_READY ; 
 scalar_t__ DIVA_DFIFO_STEP ; 
 char DIVA_DFIFO_WRAP ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ; 

int diva_istream_write(void *context,
		       int Id,
		       void *data,
		       int length,
		       int final,
		       byte usr1,
		       byte usr2) {
	ADAPTER *a = (ADAPTER *)context;
	int written = 0, to_write = -1;
	char tmp[4];
	byte *data_ptr = (byte *)data;
	for (;;) {
		a->ram_in_dw(a,
#ifdef PLATFORM_GT_32BIT
			      ULongToPtr(a->tx_stream[Id] + a->tx_pos[Id]),
#else
			      (void *)(a->tx_stream[Id] + a->tx_pos[Id]),
#endif
			      (dword *)&tmp[0],
			      1);
		if (tmp[0] & DIVA_DFIFO_READY) { /* No free blocks more */
			if (to_write < 0)
				return (-1); /* was not able to write       */
			break;     /* only part of message was written */
		}
		to_write = min(length, DIVA_DFIFO_DATA_SZ);
		if (to_write) {
			a->ram_out_buffer(a,
#ifdef PLATFORM_GT_32BIT
					   ULongToPtr(a->tx_stream[Id] + a->tx_pos[Id] + 4),
#else
					   (void *)(a->tx_stream[Id] + a->tx_pos[Id] + 4),
#endif
					   data_ptr,
					   (word)to_write);
			length  -= to_write;
			written  += to_write;
			data_ptr += to_write;
		}
		tmp[1] = (char)to_write;
		tmp[0] = (tmp[0] & DIVA_DFIFO_WRAP) |
			DIVA_DFIFO_READY |
			((!length && final) ? DIVA_DFIFO_LAST : 0);
		if (tmp[0] & DIVA_DFIFO_LAST) {
			tmp[2] = usr1;
			tmp[3] = usr2;
		}
		a->ram_out_dw(a,
#ifdef PLATFORM_GT_32BIT
			       ULongToPtr(a->tx_stream[Id] + a->tx_pos[Id]),
#else
			       (void *)(a->tx_stream[Id] + a->tx_pos[Id]),
#endif
			       (dword *)&tmp[0],
			       1);
		if (tmp[0] & DIVA_DFIFO_WRAP) {
			a->tx_pos[Id]  = 0;
		} else {
			a->tx_pos[Id] += DIVA_DFIFO_STEP;
		}
		if (!length) {
			break;
		}
	}
	return (written);
}