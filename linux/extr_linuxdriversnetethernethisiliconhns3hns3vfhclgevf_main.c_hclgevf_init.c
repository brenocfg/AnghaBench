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

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_NAME ; 
 int /*<<< orphan*/  ae_algovf ; 
 int /*<<< orphan*/  hnae3_register_ae_algo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_init(void)
{
	pr_info("%s is initializing\n", HCLGEVF_NAME);

	hnae3_register_ae_algo(&ae_algovf);

	return 0;
}