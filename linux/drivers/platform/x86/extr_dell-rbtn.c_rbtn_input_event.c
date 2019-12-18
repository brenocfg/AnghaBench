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
struct rbtn_data {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_RFKILL ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbtn_input_event(struct rbtn_data *rbtn_data)
{
	input_report_key(rbtn_data->input_dev, KEY_RFKILL, 1);
	input_sync(rbtn_data->input_dev);
	input_report_key(rbtn_data->input_dev, KEY_RFKILL, 0);
	input_sync(rbtn_data->input_dev);
}