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
struct TYPE_2__ {char sign; int realbits; int storagebits; } ;
struct iio_chan_spec {int channel; int scan_index; TYPE_1__ scan_type; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_TIMESTAMP ; 

__attribute__((used)) static void ad7280_timestamp_channel_init(struct iio_chan_spec *chan, int cnt)
{
	chan->type = IIO_TIMESTAMP;
	chan->channel = -1;
	chan->scan_index = cnt;
	chan->scan_type.sign = 's';
	chan->scan_type.realbits = 64;
	chan->scan_type.storagebits = 64;
}