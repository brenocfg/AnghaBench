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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dib9000_state {int /*<<< orphan*/  fe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,char*,...) ; 

__attribute__((used)) static int dib9000_risc_debug_buf(struct dib9000_state *state, u16 * data, u8 size)
{
	u32 ts = data[1] << 16 | data[0];
	char *b = (char *)&data[2];

	b[2 * (size - 2) - 1] = '\0';	/* Bullet proof the buffer */
	if (*b == '~') {
		b++;
		dprintk("%s\n", b);
	} else
		dprintk("RISC%d: %d.%04d %s\n",
			state->fe_id,
			ts / 10000, ts % 10000, *b ? b : "<empty>");
	return 1;
}