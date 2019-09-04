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
struct hclgevf_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclgevf_uninit_hdev (struct hclgevf_dev*) ; 

__attribute__((used)) static void hclgevf_uninit_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct hclgevf_dev *hdev = ae_dev->priv;

	hclgevf_uninit_hdev(hdev);
	ae_dev->priv = NULL;
}