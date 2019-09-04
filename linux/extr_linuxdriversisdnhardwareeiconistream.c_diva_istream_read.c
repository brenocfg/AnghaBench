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
struct TYPE_5__ {scalar_t__* rx_pos; scalar_t__* rx_stream; int /*<<< orphan*/  (* ram_out_dw ) (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* ram_in_buffer ) (TYPE_1__*,void*,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ram_in_dw ) (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ ADAPTER ;

/* Variables and functions */
 char DIVA_DFIFO_LAST ; 
 char DIVA_DFIFO_READY ; 
 scalar_t__ DIVA_DFIFO_STEP ; 
 char DIVA_DFIFO_WRAP ; 
 int min (int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,void*,int /*<<< orphan*/ *,int) ; 

int diva_istream_read(void *context,
		      int Id,
		      void *data,
		      int max_length,
		      int *final,
		      byte *usr1,
		      byte *usr2) {
	ADAPTER *a = (ADAPTER *)context;
	int read = 0, to_read = -1;
	char tmp[4];
	byte *data_ptr = (byte *)data;
	*final = 0;
	for (;;) {
		a->ram_in_dw(a,
#ifdef PLATFORM_GT_32BIT
			      ULongToPtr(a->rx_stream[Id] + a->rx_pos[Id]),
#else
			      (void *)(a->rx_stream[Id] + a->rx_pos[Id]),
#endif
			      (dword *)&tmp[0],
			      1);
		if (tmp[1] > max_length) {
			if (to_read < 0)
				return (-2); /* was not able to read */
			break;
		}
		if (!(tmp[0] & DIVA_DFIFO_READY)) {
			if (to_read < 0)
				return (-1); /* was not able to read */
			break;
		}
		to_read = min(max_length, (int)tmp[1]);
		if (to_read) {
			a->ram_in_buffer(a,
#ifdef PLATFORM_GT_32BIT
					 ULongToPtr(a->rx_stream[Id] + a->rx_pos[Id] + 4),
#else
					 (void *)(a->rx_stream[Id] + a->rx_pos[Id] + 4),
#endif
					 data_ptr,
					 (word)to_read);
			max_length -= to_read;
			read     += to_read;
			data_ptr  += to_read;
		}
		if (tmp[0] & DIVA_DFIFO_LAST) {
			*final = 1;
		}
		tmp[0] &= DIVA_DFIFO_WRAP;
		a->ram_out_dw(a,
#ifdef PLATFORM_GT_32BIT
			      ULongToPtr(a->rx_stream[Id] + a->rx_pos[Id]),
#else
			      (void *)(a->rx_stream[Id] + a->rx_pos[Id]),
#endif
			      (dword *)&tmp[0],
			      1);
		if (tmp[0] & DIVA_DFIFO_WRAP) {
			a->rx_pos[Id]  = 0;
		} else {
			a->rx_pos[Id] += DIVA_DFIFO_STEP;
		}
		if (*final) {
			if (usr1)
				*usr1 = tmp[2];
			if (usr2)
				*usr2 = tmp[3];
			break;
		}
	}
	return (read);
}