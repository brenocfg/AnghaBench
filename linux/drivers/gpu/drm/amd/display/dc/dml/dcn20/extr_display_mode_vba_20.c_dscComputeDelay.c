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
typedef  enum output_format_class { ____Placeholder_output_format_class } output_format_class ;

/* Variables and functions */
 int dm_420 ; 
 int dm_n422 ; 

__attribute__((used)) static unsigned int dscComputeDelay(enum output_format_class pixelFormat)
{
	unsigned int Delay = 0;

	if (pixelFormat == dm_420) {
		//   sfr
		Delay = Delay + 2;
		//   dsccif
		Delay = Delay + 0;
		//   dscc - input deserializer
		Delay = Delay + 3;
		//   dscc gets pixels every other cycle
		Delay = Delay + 2;
		//   dscc - input cdc fifo
		Delay = Delay + 12;
		//   dscc gets pixels every other cycle
		Delay = Delay + 13;
		//   dscc - cdc uncertainty
		Delay = Delay + 2;
		//   dscc - output cdc fifo
		Delay = Delay + 7;
		//   dscc gets pixels every other cycle
		Delay = Delay + 3;
		//   dscc - cdc uncertainty
		Delay = Delay + 2;
		//   dscc - output serializer
		Delay = Delay + 1;
		//   sft
		Delay = Delay + 1;
	} else if (pixelFormat == dm_n422) {
		//   sfr
		Delay = Delay + 2;
		//   dsccif
		Delay = Delay + 1;
		//   dscc - input deserializer
		Delay = Delay + 5;
		//  dscc - input cdc fifo
		Delay = Delay + 25;
		//   dscc - cdc uncertainty
		Delay = Delay + 2;
		//   dscc - output cdc fifo
		Delay = Delay + 10;
		//   dscc - cdc uncertainty
		Delay = Delay + 2;
		//   dscc - output serializer
		Delay = Delay + 1;
		//   sft
		Delay = Delay + 1;
	} else {
		//   sfr
		Delay = Delay + 2;
		//   dsccif
		Delay = Delay + 0;
		//   dscc - input deserializer
		Delay = Delay + 3;
		//   dscc - input cdc fifo
		Delay = Delay + 12;
		//   dscc - cdc uncertainty
		Delay = Delay + 2;
		//   dscc - output cdc fifo
		Delay = Delay + 7;
		//   dscc - output serializer
		Delay = Delay + 1;
		//   dscc - cdc uncertainty
		Delay = Delay + 2;
		//   sft
		Delay = Delay + 1;
	}

	return Delay;
}