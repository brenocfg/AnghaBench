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
struct serio_raw {int dead; int /*<<< orphan*/  kref; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct serio_raw* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_raw_free ; 
 int /*<<< orphan*/  serio_raw_hangup (struct serio_raw*) ; 
 int /*<<< orphan*/  serio_raw_mutex ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serio_raw_disconnect(struct serio *serio)
{
	struct serio_raw *serio_raw = serio_get_drvdata(serio);

	misc_deregister(&serio_raw->dev);

	mutex_lock(&serio_raw_mutex);
	serio_raw->dead = true;
	list_del_init(&serio_raw->node);
	mutex_unlock(&serio_raw_mutex);

	serio_raw_hangup(serio_raw);

	serio_close(serio);
	kref_put(&serio_raw->kref, serio_raw_free);

	serio_set_drvdata(serio, NULL);
}