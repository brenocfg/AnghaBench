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
struct rbsp {int* data; int pos; scalar_t__ size; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static void nal_h264_read_filler_data(struct rbsp *rbsp)
{
	u8 *p = rbsp->data + DIV_ROUND_UP(rbsp->pos, 8);

	while (*p == 0xff) {
		if (DIV_ROUND_UP(rbsp->pos, 8) > rbsp->size) {
			rbsp->error = -EINVAL;
			return;
		}

		p++;
		rbsp->pos += 8;
	}
}