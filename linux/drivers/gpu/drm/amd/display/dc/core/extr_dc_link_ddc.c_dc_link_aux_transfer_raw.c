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
struct ddc_service {int dummy; } ;
struct aux_payload {int dummy; } ;
typedef  enum aux_channel_operation_result { ____Placeholder_aux_channel_operation_result } aux_channel_operation_result ;

/* Variables and functions */
 int dce_aux_transfer_raw (struct ddc_service*,struct aux_payload*,int*) ; 

int dc_link_aux_transfer_raw(struct ddc_service *ddc,
		struct aux_payload *payload,
		enum aux_channel_operation_result *operation_result)
{
	return dce_aux_transfer_raw(ddc, payload, operation_result);
}