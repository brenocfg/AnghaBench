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
struct usb_function {int dummy; } ;
struct f_sourcesink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_source_sink (struct f_sourcesink*) ; 
 struct f_sourcesink* func_to_ss (struct usb_function*) ; 

__attribute__((used)) static void sourcesink_disable(struct usb_function *f)
{
	struct f_sourcesink	*ss = func_to_ss(f);

	disable_source_sink(ss);
}