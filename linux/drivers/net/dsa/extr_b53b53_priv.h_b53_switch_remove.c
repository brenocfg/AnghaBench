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
struct b53_device {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void b53_switch_remove(struct b53_device *dev)
{
	dsa_unregister_switch(dev->ds);
}