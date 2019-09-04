#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int RX_ALIGNMENT_ERROR ; 
 int RX_FCS_ERR ; 
 int RX_FIFO_OVERRUN ; 
 int RX_LENGTH_ERR ; 

__attribute__((used)) static void nb8800_rx_error(struct net_device *dev, u32 report)
{
	if (report & RX_LENGTH_ERR)
		dev->stats.rx_length_errors++;

	if (report & RX_FCS_ERR)
		dev->stats.rx_crc_errors++;

	if (report & RX_FIFO_OVERRUN)
		dev->stats.rx_fifo_errors++;

	if (report & RX_ALIGNMENT_ERROR)
		dev->stats.rx_frame_errors++;

	dev->stats.rx_errors++;
}