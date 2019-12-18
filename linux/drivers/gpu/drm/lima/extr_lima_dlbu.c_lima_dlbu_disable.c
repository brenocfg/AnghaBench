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
struct lima_ip {int dummy; } ;
struct lima_device {struct lima_ip* ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_DLBU_PP_ENABLE_MASK ; 
 int /*<<< orphan*/  dlbu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lima_ip_dlbu ; 

void lima_dlbu_disable(struct lima_device *dev)
{
	struct lima_ip *ip = dev->ip + lima_ip_dlbu;

	dlbu_write(LIMA_DLBU_PP_ENABLE_MASK, 0);
}