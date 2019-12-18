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
struct device {int dummy; } ;
struct anybuss_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  anybuss_host_common_remove (struct anybuss_host*) ; 

__attribute__((used)) static void host_release(struct device *dev, void *res)
{
	struct anybuss_host **dr = res;

	anybuss_host_common_remove(*dr);
}