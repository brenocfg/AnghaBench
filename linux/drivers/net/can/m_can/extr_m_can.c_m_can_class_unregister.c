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
struct m_can_classdev {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_clk_stop (struct m_can_classdev*) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 

void m_can_class_unregister(struct m_can_classdev *m_can_dev)
{
	unregister_candev(m_can_dev->net);

	m_can_clk_stop(m_can_dev);

	free_candev(m_can_dev->net);
}