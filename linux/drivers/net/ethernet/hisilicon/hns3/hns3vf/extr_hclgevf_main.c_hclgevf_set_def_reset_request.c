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
struct hnae3_ae_dev {struct hclgevf_dev* priv; } ;
struct hclgevf_dev {int /*<<< orphan*/  default_reset_request; } ;
typedef  enum hnae3_reset_type { ____Placeholder_hnae3_reset_type } hnae3_reset_type ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclgevf_set_def_reset_request(struct hnae3_ae_dev *ae_dev,
					  enum hnae3_reset_type rst_type)
{
	struct hclgevf_dev *hdev = ae_dev->priv;

	set_bit(rst_type, &hdev->default_reset_request);
}