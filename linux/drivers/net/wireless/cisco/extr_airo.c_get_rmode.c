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
typedef  int __le16 ;

/* Variables and functions */
#define  RXMODE_LANMON 130 
 int RXMODE_MASK ; 
#define  RXMODE_RFMON 129 
#define  RXMODE_RFMON_ANYBSS 128 

__attribute__((used)) static const char *get_rmode(__le16 mode)
{
        switch(mode & RXMODE_MASK) {
        case RXMODE_RFMON:  return "rfmon";
        case RXMODE_RFMON_ANYBSS:  return "yna (any) bss rfmon";
        case RXMODE_LANMON:  return "lanmon";
        }
        return "ESS";
}