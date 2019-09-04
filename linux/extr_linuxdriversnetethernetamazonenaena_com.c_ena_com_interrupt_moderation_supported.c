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
struct ena_com_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_INTERRUPT_MODERATION ; 
 int ena_com_check_supported_feature_id (struct ena_com_dev*,int /*<<< orphan*/ ) ; 

bool ena_com_interrupt_moderation_supported(struct ena_com_dev *ena_dev)
{
	return ena_com_check_supported_feature_id(ena_dev,
						  ENA_ADMIN_INTERRUPT_MODERATION);
}