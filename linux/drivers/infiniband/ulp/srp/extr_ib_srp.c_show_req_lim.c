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
struct srp_target_port {int ch_count; struct srp_rdma_ch* ch; } ;
struct srp_rdma_ch {int /*<<< orphan*/  req_lim; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 struct srp_target_port* host_to_target (int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_req_lim(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	struct srp_target_port *target = host_to_target(class_to_shost(dev));
	struct srp_rdma_ch *ch;
	int i, req_lim = INT_MAX;

	for (i = 0; i < target->ch_count; i++) {
		ch = &target->ch[i];
		req_lim = min(req_lim, ch->req_lim);
	}
	return sprintf(buf, "%d\n", req_lim);
}