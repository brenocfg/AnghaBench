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
struct vchiq_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_service_closing_internal (struct vchiq_service*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_service_closing(struct vchiq_service *service)
{
	mark_service_closing_internal(service, 0);
}