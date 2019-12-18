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
struct nvdimm {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 void const* key_data (struct key*) ; 
 struct key* nvdimm_request_key (struct nvdimm*) ; 
 void const* zero_key ; 

__attribute__((used)) static const void *nvdimm_get_key_payload(struct nvdimm *nvdimm,
		struct key **key)
{
	*key = nvdimm_request_key(nvdimm);
	if (!*key)
		return zero_key;

	return key_data(*key);
}