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
typedef  int u8 ;

/* Variables and functions */
 int RTLLIB_BASIC_RATE_MASK ; 
#define  RTLLIB_OFDM_RATE_12MB 135 
#define  RTLLIB_OFDM_RATE_18MB 134 
#define  RTLLIB_OFDM_RATE_24MB 133 
#define  RTLLIB_OFDM_RATE_36MB 132 
#define  RTLLIB_OFDM_RATE_48MB 131 
#define  RTLLIB_OFDM_RATE_54MB 130 
#define  RTLLIB_OFDM_RATE_6MB 129 
#define  RTLLIB_OFDM_RATE_9MB 128 

__attribute__((used)) static inline int rtllib_is_ofdm_rate(u8 rate)
{
	switch (rate & ~RTLLIB_BASIC_RATE_MASK) {
	case RTLLIB_OFDM_RATE_6MB:
	case RTLLIB_OFDM_RATE_9MB:
	case RTLLIB_OFDM_RATE_12MB:
	case RTLLIB_OFDM_RATE_18MB:
	case RTLLIB_OFDM_RATE_24MB:
	case RTLLIB_OFDM_RATE_36MB:
	case RTLLIB_OFDM_RATE_48MB:
	case RTLLIB_OFDM_RATE_54MB:
		return 1;
	}
	return 0;
}