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
struct TYPE_2__ {scalar_t__ container; } ;
struct aux_payloads {TYPE_1__ payloads; } ;
struct aux_payload {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct aux_payload *dal_ddc_aux_payloads_get(struct aux_payloads *p)
{
	return (struct aux_payload *)p->payloads.container;
}