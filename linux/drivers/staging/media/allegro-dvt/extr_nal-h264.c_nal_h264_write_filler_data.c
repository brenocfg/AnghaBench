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
typedef  int /*<<< orphan*/  u8 ;
struct rbsp {int pos; int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void nal_h264_write_filler_data(struct rbsp *rbsp)
{
	u8 *p = rbsp->data + DIV_ROUND_UP(rbsp->pos, 8);
	int i;

	/* Keep 1 byte extra for terminating the NAL unit */
	i = rbsp->size - DIV_ROUND_UP(rbsp->pos, 8) - 1;
	memset(p, 0xff, i);
	rbsp->pos += i * 8;
}