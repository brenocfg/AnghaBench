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
struct imgu_css_buffer {int state; } ;
typedef  enum imgu_css_buffer_state { ____Placeholder_imgu_css_buffer_state } imgu_css_buffer_state ;

/* Variables and functions */

__attribute__((used)) static inline enum imgu_css_buffer_state
imgu_css_buf_state(struct imgu_css_buffer *b)
{
	return b->state;
}