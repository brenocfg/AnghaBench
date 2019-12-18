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
struct ib_mad_hdr {int /*<<< orphan*/  tid; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; int /*<<< orphan*/  class_version; int /*<<< orphan*/  mgmt_class; int /*<<< orphan*/  base_version; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CM_CLASS_VERSION ; 
 int /*<<< orphan*/  IB_MGMT_BASE_VERSION ; 
 int /*<<< orphan*/  IB_MGMT_CLASS_CM ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_SEND ; 

__attribute__((used)) static void cm_format_mad_hdr(struct ib_mad_hdr *hdr,
			      __be16 attr_id, __be64 tid)
{
	hdr->base_version  = IB_MGMT_BASE_VERSION;
	hdr->mgmt_class	   = IB_MGMT_CLASS_CM;
	hdr->class_version = IB_CM_CLASS_VERSION;
	hdr->method	   = IB_MGMT_METHOD_SEND;
	hdr->attr_id	   = attr_id;
	hdr->tid	   = tid;
}