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
struct nbu2ss_udc {int dummy; } ;

/* Variables and functions */
 int _nbu2ss_req_feature (struct nbu2ss_udc*,int) ; 

__attribute__((used)) static int std_req_set_feature(struct nbu2ss_udc *udc)
{
	return _nbu2ss_req_feature(udc, true);
}