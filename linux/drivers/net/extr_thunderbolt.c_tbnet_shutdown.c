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
struct tb_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_service_get_drvdata (struct tb_service*) ; 
 int /*<<< orphan*/  tbnet_tear_down (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tbnet_shutdown(struct tb_service *svc)
{
	tbnet_tear_down(tb_service_get_drvdata(svc), true);
}