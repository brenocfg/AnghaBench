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
struct iw_cm_id {struct c4iw_listen_ep* provider_data; } ;
struct c4iw_listen_ep {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct c4iw_listen_ep *to_listen_ep(struct iw_cm_id *cm_id)
{
	return cm_id->provider_data;
}