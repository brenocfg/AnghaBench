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
struct hsi_msg {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ HSI_STATUS_COMPLETED ; 
 scalar_t__ HSI_STATUS_ERROR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 

__attribute__((used)) static void cs_hsi_free_data_msg(struct hsi_msg *msg)
{
	WARN_ON(msg->status != HSI_STATUS_COMPLETED &&
					msg->status != HSI_STATUS_ERROR);
	hsi_free_msg(msg);
}