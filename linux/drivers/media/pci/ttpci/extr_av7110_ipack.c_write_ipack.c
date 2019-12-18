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
struct ipack {int count; int buf; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,int const*,int) ; 
 int /*<<< orphan*/  send_ipack (struct ipack*) ; 

__attribute__((used)) static void write_ipack(struct ipack *p, const u8 *data, int count)
{
	u8 headr[3] = { 0x00, 0x00, 0x01 };

	if (p->count < 6) {
		memcpy(p->buf, headr, 3);
		p->count = 6;
	}

	if (p->count + count < p->size){
		memcpy(p->buf+p->count, data, count);
		p->count += count;
	} else {
		int rest = p->size - p->count;
		memcpy(p->buf+p->count, data, rest);
		p->count += rest;
		send_ipack(p);
		if (count - rest > 0)
			write_ipack(p, data + rest, count - rest);
	}
}