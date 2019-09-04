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
 int /*<<< orphan*/  ae_algo ; 
 int /*<<< orphan*/  hnae3_unregister_ae_algo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_exit(void)
{
	hnae3_unregister_ae_algo(&ae_algo);
}