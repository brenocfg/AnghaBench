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
typedef  int u16 ;
struct nct6775_data {int kind; } ;

/* Variables and functions */
#define  nct6106 136 
#define  nct6775 135 
#define  nct6776 134 
#define  nct6779 133 
#define  nct6791 132 
#define  nct6792 131 
#define  nct6793 130 
#define  nct6795 129 
#define  nct6796 128 

__attribute__((used)) static bool is_word_sized(struct nct6775_data *data, u16 reg)
{
	switch (data->kind) {
	case nct6106:
		return reg == 0x20 || reg == 0x22 || reg == 0x24 ||
		  reg == 0xe0 || reg == 0xe2 || reg == 0xe4 ||
		  reg == 0x111 || reg == 0x121 || reg == 0x131;
	case nct6775:
		return (((reg & 0xff00) == 0x100 ||
		    (reg & 0xff00) == 0x200) &&
		   ((reg & 0x00ff) == 0x50 ||
		    (reg & 0x00ff) == 0x53 ||
		    (reg & 0x00ff) == 0x55)) ||
		  (reg & 0xfff0) == 0x630 ||
		  reg == 0x640 || reg == 0x642 ||
		  reg == 0x662 ||
		  ((reg & 0xfff0) == 0x650 && (reg & 0x000f) >= 0x06) ||
		  reg == 0x73 || reg == 0x75 || reg == 0x77;
	case nct6776:
		return (((reg & 0xff00) == 0x100 ||
		    (reg & 0xff00) == 0x200) &&
		   ((reg & 0x00ff) == 0x50 ||
		    (reg & 0x00ff) == 0x53 ||
		    (reg & 0x00ff) == 0x55)) ||
		  (reg & 0xfff0) == 0x630 ||
		  reg == 0x402 ||
		  reg == 0x640 || reg == 0x642 ||
		  ((reg & 0xfff0) == 0x650 && (reg & 0x000f) >= 0x06) ||
		  reg == 0x73 || reg == 0x75 || reg == 0x77;
	case nct6779:
	case nct6791:
	case nct6792:
	case nct6793:
	case nct6795:
	case nct6796:
		return reg == 0x150 || reg == 0x153 || reg == 0x155 ||
		  (reg & 0xfff0) == 0x4c0 ||
		  reg == 0x402 ||
		  reg == 0x63a || reg == 0x63c || reg == 0x63e ||
		  reg == 0x640 || reg == 0x642 || reg == 0x64a ||
		  reg == 0x64c ||
		  reg == 0x73 || reg == 0x75 || reg == 0x77 || reg == 0x79 ||
		  reg == 0x7b || reg == 0x7d;
	}
	return false;
}