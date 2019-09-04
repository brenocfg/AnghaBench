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
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
#define  _PAGE_CACHE_MODE_UC 133 
#define  _PAGE_CACHE_MODE_UC_MINUS 132 
#define  _PAGE_CACHE_MODE_WB 131 
#define  _PAGE_CACHE_MODE_WC 130 
#define  _PAGE_CACHE_MODE_WP 129 
#define  _PAGE_CACHE_MODE_WT 128 

__attribute__((used)) static inline char *cattr_name(enum page_cache_mode pcm)
{
	switch (pcm) {
	case _PAGE_CACHE_MODE_UC:		return "uncached";
	case _PAGE_CACHE_MODE_UC_MINUS:		return "uncached-minus";
	case _PAGE_CACHE_MODE_WB:		return "write-back";
	case _PAGE_CACHE_MODE_WC:		return "write-combining";
	case _PAGE_CACHE_MODE_WT:		return "write-through";
	case _PAGE_CACHE_MODE_WP:		return "write-protected";
	default:				return "broken";
	}
}