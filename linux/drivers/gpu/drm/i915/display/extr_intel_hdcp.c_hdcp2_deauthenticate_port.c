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
struct intel_connector {int dummy; } ;

/* Variables and functions */
 int hdcp2_close_mei_session (struct intel_connector*) ; 

__attribute__((used)) static int hdcp2_deauthenticate_port(struct intel_connector *connector)
{
	return hdcp2_close_mei_session(connector);
}