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
struct TYPE_2__ {int options; } ;
struct aac_dev {TYPE_1__ adapter_info; } ;

/* Variables and functions */
 int AAC_OPT_NEW_COMM_64 ; 

__attribute__((used)) static inline int aac_supports_2T(struct aac_dev *dev)
{
	return (dev->adapter_info.options & AAC_OPT_NEW_COMM_64);
}