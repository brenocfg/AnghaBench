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
struct rbsp {int /*<<< orphan*/  pos; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned int FILLER_DATA ; 
 int /*<<< orphan*/  nal_h264_rbsp_trailing_bits (struct rbsp*) ; 
 int /*<<< orphan*/  nal_h264_write_filler_data (struct rbsp*) ; 
 int /*<<< orphan*/  nal_h264_write_start_code_prefix (struct rbsp*) ; 
 int /*<<< orphan*/  rbsp_bit (struct rbsp*,unsigned int*) ; 
 int /*<<< orphan*/  rbsp_bits (struct rbsp*,int,unsigned int*) ; 
 int /*<<< orphan*/  rbsp_init (struct rbsp*,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write ; 

ssize_t nal_h264_write_filler(const struct device *dev, void *dest, size_t n)
{
	struct rbsp rbsp;
	unsigned int forbidden_zero_bit = 0;
	unsigned int nal_ref_idc = 0;
	unsigned int nal_unit_type = FILLER_DATA;

	if (!dest)
		return -EINVAL;

	rbsp_init(&rbsp, dest, n, &write);

	nal_h264_write_start_code_prefix(&rbsp);

	rbsp_bit(&rbsp, &forbidden_zero_bit);
	rbsp_bits(&rbsp, 2, &nal_ref_idc);
	rbsp_bits(&rbsp, 5, &nal_unit_type);

	nal_h264_write_filler_data(&rbsp);

	nal_h264_rbsp_trailing_bits(&rbsp);

	return DIV_ROUND_UP(rbsp.pos, 8);
}