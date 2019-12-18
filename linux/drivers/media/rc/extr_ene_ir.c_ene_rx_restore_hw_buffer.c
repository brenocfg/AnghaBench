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
struct ene_device {int extra_buf1_address; int extra_buf1_len; int extra_buf2_address; int extra_buf2_len; int /*<<< orphan*/  hw_extra_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_FW1 ; 
 int /*<<< orphan*/  ENE_FW1_EXTRA_BUF_HND ; 
 scalar_t__ ENE_FW_SAMPLE_BUFFER ; 
 int /*<<< orphan*/  ene_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,scalar_t__,int) ; 

__attribute__((used)) static void ene_rx_restore_hw_buffer(struct ene_device *dev)
{
	if (!dev->hw_extra_buffer)
		return;

	ene_write_reg(dev, ENE_FW_SAMPLE_BUFFER + 0,
				dev->extra_buf1_address & 0xFF);
	ene_write_reg(dev, ENE_FW_SAMPLE_BUFFER + 1,
				dev->extra_buf1_address >> 8);
	ene_write_reg(dev, ENE_FW_SAMPLE_BUFFER + 2, dev->extra_buf1_len);

	ene_write_reg(dev, ENE_FW_SAMPLE_BUFFER + 3,
				dev->extra_buf2_address & 0xFF);
	ene_write_reg(dev, ENE_FW_SAMPLE_BUFFER + 4,
				dev->extra_buf2_address >> 8);
	ene_write_reg(dev, ENE_FW_SAMPLE_BUFFER + 5,
				dev->extra_buf2_len);
	ene_clear_reg_mask(dev, ENE_FW1, ENE_FW1_EXTRA_BUF_HND);
}