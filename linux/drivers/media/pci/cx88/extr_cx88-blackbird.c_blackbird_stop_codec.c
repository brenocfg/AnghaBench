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
struct cx8802_dev {int /*<<< orphan*/  cxhdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKBIRD_END_NOW ; 
 int /*<<< orphan*/  BLACKBIRD_MPEG_CAPTURE ; 
 int /*<<< orphan*/  BLACKBIRD_RAW_BITS_NONE ; 
 int /*<<< orphan*/  CX2341X_ENC_STOP_CAPTURE ; 
 int /*<<< orphan*/  blackbird_api_cmd (struct cx8802_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx2341x_handler_set_busy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blackbird_stop_codec(struct cx8802_dev *dev)
{
	blackbird_api_cmd(dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
			  BLACKBIRD_END_NOW,
			  BLACKBIRD_MPEG_CAPTURE,
			  BLACKBIRD_RAW_BITS_NONE);

	cx2341x_handler_set_busy(&dev->cxhdl, 0);

	return 0;
}