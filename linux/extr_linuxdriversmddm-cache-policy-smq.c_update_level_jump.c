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
struct smq_policy {unsigned int hotspot_level_jump; int /*<<< orphan*/  hotspot_stats; } ;

/* Variables and functions */
#define  Q_FAIR 130 
#define  Q_POOR 129 
#define  Q_WELL 128 
 int stats_assess (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_level_jump(struct smq_policy *mq)
{
	switch (stats_assess(&mq->hotspot_stats)) {
	case Q_POOR:
		mq->hotspot_level_jump = 4u;
		break;

	case Q_FAIR:
		mq->hotspot_level_jump = 2u;
		break;

	case Q_WELL:
		mq->hotspot_level_jump = 1u;
		break;
	}
}