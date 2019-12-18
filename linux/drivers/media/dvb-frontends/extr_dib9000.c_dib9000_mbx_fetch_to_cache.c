#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_3__ {int** message_cache; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {TYPE_2__ platform; } ;

/* Variables and functions */
 int DIB9000_MSG_CACHE_SIZE ; 
#define  IN_MSG_DATA 129 
#define  IN_MSG_DEBUG_BUF 128 
 int /*<<< orphan*/  dib9000_mbx_read (struct dib9000_state*,int*,int,int) ; 
 int /*<<< orphan*/  dib9000_risc_data_process (struct dib9000_state*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib9000_risc_debug_buf (struct dib9000_state*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib9000_mbx_fetch_to_cache(struct dib9000_state *state, u16 attr)
{
	int i;
	u8 size;
	u16 *block;
	/* find a free slot */
	for (i = 0; i < DIB9000_MSG_CACHE_SIZE; i++) {
		block = state->platform.risc.message_cache[i];
		if (*block == 0) {
			size = dib9000_mbx_read(state, block, 1, attr);

/*                      dprintk( "MBX: fetched %04x message to cache\n", *block); */

			switch (*block >> 8) {
			case IN_MSG_DEBUG_BUF:
				dib9000_risc_debug_buf(state, block + 1, size);	/* debug-messages are going to be printed right away */
				*block = 0;	/* free the block */
				break;
#if 0
			case IN_MSG_DATA:	/* FE-TRACE */
				dib9000_risc_data_process(state, block + 1, size);
				*block = 0;
				break;
#endif
			default:
				break;
			}

			return 1;
		}
	}
	dprintk("MBX: no free cache-slot found for new message...\n");
	return -1;
}