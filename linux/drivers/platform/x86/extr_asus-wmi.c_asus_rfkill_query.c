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
struct rfkill {int dummy; } ;
struct asus_rfkill {int /*<<< orphan*/  rfkill; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  asus; } ;

/* Variables and functions */
 int asus_wmi_get_devstate_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asus_rfkill_query(struct rfkill *rfkill, void *data)
{
	struct asus_rfkill *priv = data;
	int result;

	result = asus_wmi_get_devstate_simple(priv->asus, priv->dev_id);

	if (result < 0)
		return;

	rfkill_set_sw_state(priv->rfkill, !result);
}