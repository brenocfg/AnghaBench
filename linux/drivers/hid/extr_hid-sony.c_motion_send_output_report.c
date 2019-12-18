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
struct sony_sc {int /*<<< orphan*/  left; int /*<<< orphan*/  right; int /*<<< orphan*/ * led_state; scalar_t__ output_report_dmabuf; struct hid_device* hdev; } ;
struct motion_output_report_02 {int type; int /*<<< orphan*/  rumble; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOTION_REPORT_0x02_SIZE ; 
 int /*<<< orphan*/  hid_hw_output_report (struct hid_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct motion_output_report_02*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void motion_send_output_report(struct sony_sc *sc)
{
	struct hid_device *hdev = sc->hdev;
	struct motion_output_report_02 *report =
		(struct motion_output_report_02 *)sc->output_report_dmabuf;

	memset(report, 0, MOTION_REPORT_0x02_SIZE);

	report->type = 0x02; /* set leds */
	report->r = sc->led_state[0];
	report->g = sc->led_state[1];
	report->b = sc->led_state[2];

#ifdef CONFIG_SONY_FF
	report->rumble = max(sc->right, sc->left);
#endif

	hid_hw_output_report(hdev, (u8 *)report, MOTION_REPORT_0x02_SIZE);
}