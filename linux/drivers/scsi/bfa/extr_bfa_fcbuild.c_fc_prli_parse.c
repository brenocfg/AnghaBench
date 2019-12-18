#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  initiator; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ servparams; int /*<<< orphan*/  imagepair; } ;
struct fc_prli_s {TYPE_2__ parampage; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 
 scalar_t__ FC_TYPE_FCP ; 

enum fc_parse_status
fc_prli_parse(struct fc_prli_s *prli)
{
	if (prli->parampage.type != FC_TYPE_FCP)
		return FC_PARSE_FAILURE;

	if (!prli->parampage.imagepair)
		return FC_PARSE_FAILURE;

	if (!prli->parampage.servparams.initiator)
		return FC_PARSE_FAILURE;

	return FC_PARSE_OK;
}