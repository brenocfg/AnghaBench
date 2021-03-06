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
struct ipaq_micro_keys {TYPE_1__* micro; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct ipaq_micro_keys* key_data; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  micro_key_receive ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void micro_key_start(struct ipaq_micro_keys *keys)
{
	spin_lock(&keys->micro->lock);
	keys->micro->key = micro_key_receive;
	keys->micro->key_data = keys;
	spin_unlock(&keys->micro->lock);
}