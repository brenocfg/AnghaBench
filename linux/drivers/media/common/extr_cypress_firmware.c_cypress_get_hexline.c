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
struct hexline {int len; int addr; int type; int chk; int /*<<< orphan*/  data; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (struct hexline*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cypress_get_hexline(const struct firmware *fw,
				struct hexline *hx, int *pos)
{
	u8 *b = (u8 *) &fw->data[*pos];
	int data_offs = 4;

	if (*pos >= fw->size)
		return 0;

	memset(hx, 0, sizeof(struct hexline));
	hx->len = b[0];

	if ((*pos + hx->len + 4) >= fw->size)
		return -EINVAL;

	hx->addr = b[1] | (b[2] << 8);
	hx->type = b[3];

	if (hx->type == 0x04) {
		/* b[4] and b[5] are the Extended linear address record data
		 * field */
		hx->addr |= (b[4] << 24) | (b[5] << 16);
	}

	memcpy(hx->data, &b[data_offs], hx->len);
	hx->chk = b[hx->len + data_offs];
	*pos += hx->len + 5;

	return *pos;
}