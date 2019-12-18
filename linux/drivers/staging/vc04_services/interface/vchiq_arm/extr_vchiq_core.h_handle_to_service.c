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
struct vchiq_state {struct vchiq_service** services; } ;
struct vchiq_service {int dummy; } ;
typedef  int VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int VCHIQ_MAX_SERVICES ; 
 int VCHIQ_MAX_STATES ; 
 struct vchiq_state** vchiq_states ; 

__attribute__((used)) static inline struct vchiq_service *
handle_to_service(VCHIQ_SERVICE_HANDLE_T handle)
{
	struct vchiq_state *state = vchiq_states[(handle / VCHIQ_MAX_SERVICES) &
		(VCHIQ_MAX_STATES - 1)];
	if (!state)
		return NULL;

	return state->services[handle & (VCHIQ_MAX_SERVICES - 1)];
}