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
typedef  size_t u8 ;
struct iavf_rx_ptype_decoded {int dummy; } ;

/* Variables and functions */
 struct iavf_rx_ptype_decoded* iavf_ptype_lookup ; 

__attribute__((used)) static inline struct iavf_rx_ptype_decoded decode_rx_desc_ptype(u8 ptype)
{
	return iavf_ptype_lookup[ptype];
}