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
struct comedi_lrange {int dummy; } ;

/* Variables and functions */
 struct comedi_lrange const range_bipolar10 ; 
 struct comedi_lrange const range_dt2801_ai_pgl_bipolar ; 
 struct comedi_lrange const range_dt2801_ai_pgl_unipolar ; 
 struct comedi_lrange const range_unipolar10 ; 
 struct comedi_lrange const range_unipolar5 ; 
 struct comedi_lrange const range_unknown ; 

__attribute__((used)) static const struct comedi_lrange *ai_range_lkup(int type, int opt)
{
	switch (type) {
	case 0:
		return (opt) ?
		    &range_dt2801_ai_pgl_unipolar :
		    &range_dt2801_ai_pgl_bipolar;
	case 1:
		return (opt) ? &range_unipolar10 : &range_bipolar10;
	case 2:
		return &range_unipolar5;
	}
	return &range_unknown;
}