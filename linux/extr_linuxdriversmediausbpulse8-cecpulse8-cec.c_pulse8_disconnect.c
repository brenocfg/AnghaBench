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
struct serio {int /*<<< orphan*/  dev; } ;
struct pulse8 {int /*<<< orphan*/  ping_eeprom_work; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct pulse8*) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct pulse8* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pulse8_disconnect(struct serio *serio)
{
	struct pulse8 *pulse8 = serio_get_drvdata(serio);

	cec_unregister_adapter(pulse8->adap);
	cancel_delayed_work_sync(&pulse8->ping_eeprom_work);
	dev_info(&serio->dev, "disconnected\n");
	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	kfree(pulse8);
}