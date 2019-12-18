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
struct napi_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,unsigned int) ; 
 unsigned int tun_napi_receive (struct napi_struct*,int) ; 

__attribute__((used)) static int tun_napi_poll(struct napi_struct *napi, int budget)
{
	unsigned int received;

	received = tun_napi_receive(napi, budget);

	if (received < budget)
		napi_complete_done(napi, received);

	return received;
}