#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wwn_t ;
struct TYPE_2__ {scalar_t__ els_code; } ;
struct fc_adisc_s {int /*<<< orphan*/  orig_port_name; TYPE_1__ els_cmd; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
 scalar_t__ FC_ELS_ACC ; 
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 
 int /*<<< orphan*/  wwn_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum fc_parse_status
fc_adisc_rsp_parse(struct fc_adisc_s *adisc, int len, wwn_t port_name,
				 wwn_t node_name)
{

	if (len < sizeof(struct fc_adisc_s))
		return FC_PARSE_FAILURE;

	if (adisc->els_cmd.els_code != FC_ELS_ACC)
		return FC_PARSE_FAILURE;

	if (!wwn_is_equal(adisc->orig_port_name, port_name))
		return FC_PARSE_FAILURE;

	return FC_PARSE_OK;
}